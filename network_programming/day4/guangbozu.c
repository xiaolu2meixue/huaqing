#include <myhead.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <net/if.h>  // 添加if_nametoindex所需头文件

typedef struct sockaddr_in addr_in_t;
typedef struct sockaddr addr_t;

struct ip_mreqn {
    struct in_addr imr_multiaddr;
    struct in_addr imr_address;
    int imr_ifindex;
};

int main(int argc, const char *argv[])
{
    if(argc < 2){
        fprintf(stderr, "Usage: %s <port> [interface_name]\n", argv[0]);
        return 1;
    }
    
    // 1. 初始化参数
    short port = atoi(argv[1]);
    const char* interface_name = (argc > 2) ? argv[2] : "eth0"; // 默认使用eth0接口
    
    // 2. 创建UDP套接字
    int sender = socket(AF_INET, SOCK_DGRAM, 0);
    if(sender < 0){
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 3. 设置套接字选项
    int optval = 1;
    if(setsockopt(sender, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) {
        perror("setsockopt SO_REUSEADDR");
        close(sender);
        exit(EXIT_FAILURE);
    }

    // 4. 绑定套接字
    addr_in_t local_addr = {0};
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(sender, (addr_t*)&local_addr, sizeof(local_addr)) < 0){
        perror("bind failed");
        close(sender);
        exit(EXIT_FAILURE);
    }

    // 5. 设置多播参数
    struct ip_mreqn multi_addr;
    multi_addr.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    multi_addr.imr_address.s_addr = INADDR_ANY; // 使用任意接口
    
    // 获取网络接口索引（更可靠的方式）
    unsigned int ifindex = if_nametoindex(interface_name);
    if(ifindex == 0){
        perror("if_nametoindex failed");
        close(sender);
        exit(EXIT_FAILURE);
    }
    multi_addr.imr_ifindex = ifindex;
    
    if(setsockopt(sender, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multi_addr, sizeof(multi_addr)) < 0){
        perror("setsockopt IP_ADD_MEMBERSHIP");
        close(sender);
        exit(EXIT_FAILURE);
    }

    // 6. 设置多播TTL（可选）
    unsigned char ttl = 1; // 限制在本地网络
    setsockopt(sender, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));

    // 7. 创建epoll实例
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if(epfd < 0){
        perror("epoll_create1");
        close(sender);
        exit(EXIT_FAILURE);
    }

    // 8. 添加监控事件
    struct epoll_event ev;
    ev.events = EPOLLIN;
    
    // 监控标准输入
    ev.data.fd = STDIN_FILENO;
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) < 0){
        perror("epoll_ctl stdin");
        close(sender);
        close(epfd);
        exit(EXIT_FAILURE);
    }
    
    // 监控套接字
    ev.data.fd = sender;
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, sender, &ev) < 0){
        perror("epoll_ctl sender");
        close(sender);
        close(epfd);
        exit(EXIT_FAILURE);
    }

    printf("组播程序已启动 (组播组: 224.0.0.1:%d, 接口: %s)\n", port, interface_name);

    // 9. 事件循环
    while(1){
        struct epoll_event events[2];
        int nfds = epoll_wait(epfd, events, 2, -1);
        if(nfds < 0){
            perror("epoll_wait");
            break;
        }

        for(int i = 0; i < nfds; i++){
            if(events[i].data.fd == STDIN_FILENO){
                char buf[128] = {0};
                if(fgets(buf, sizeof(buf), stdin) == NULL){
                    perror("fgets");
                    continue;
                }
                
                // 移除换行符
                buf[strcspn(buf, "\n")] = 0;
                
                // 发送到多播组
                addr_in_t multicast_addr = {
                    .sin_family = AF_INET,
                    .sin_addr.s_addr = inet_addr("224.0.0.1"),
                    .sin_port = htons(port)
                };
                
                if(sendto(sender, buf, strlen(buf), 0, 
                          (addr_t*)&multicast_addr, sizeof(multicast_addr)) < 0){
                    perror("sendto");
                }
            }
            else if(events[i].data.fd == sender){
                char buf[128] = {0};
                struct sockaddr_in src_addr;
                socklen_t addrlen = sizeof(src_addr);
                
                ssize_t len = recvfrom(sender, buf, sizeof(buf)-1, 0,
                                      (addr_t*)&src_addr, &addrlen);
                if(len > 0){
                    buf[len] = 0; // 确保字符串终止
                    printf("来自 %s:%d 的消息: %s\n", 
                           inet_ntoa(src_addr.sin_addr),
                           ntohs(src_addr.sin_port),
                           buf);
                }
            }
        }
    }

    // 10. 清理资源
    close(sender);
    close(epfd);
    return 0;
}