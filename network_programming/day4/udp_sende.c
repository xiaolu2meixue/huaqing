#include <myhead.h>
#include <sys/epoll.h>

typedef struct sockaddr_in addr_in_t;
typedef struct sockaddr addr_t;
typedef struct sockaddr_un addr_un_t;

int main(int argc, const char *argv[])
{
    if(argc < 2){
        printf("请输入端口号\n");
        return 1;
    }
    
    short port = atoi(argv[1]);
    
    int sender = socket(AF_INET,SOCK_DGRAM,0);

    int optval = 1;
    if (setsockopt(sender, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))) {
        perror("setsockopt error");
        close(sender);
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.141.255");
    addr.sin_port = htons(port);
    // udp 协议中的connect不是真正的建立连接
    // 而是将目标 ip 和 port 写入内核中
    // 内核中一旦有目标ip 和 port，就可以不再使用sendto了，使用send或者write都是可以的
    if(connect(sender,(struct sockaddr*)&addr,sizeof(addr)) == -1){
        perror("bind");
    }
    
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    struct epoll_event epoll_sender = {.events = EPOLLIN,.data.fd = sender};
    struct epoll_event epoll_stdin = {.events = EPOLLIN,.data.fd = 0};
    epoll_ctl(epfd,EPOLL_CTL_ADD,sender,&epoll_sender);
    epoll_ctl(epfd,EPOLL_CTL_ADD,0,&epoll_stdin);
    int eplen = 2;
    
    while(1){
		struct epoll_event list[10] = {0};
		int count = epoll_wait(epfd,list,eplen,-1);
		for(int i=0;i<count;i++){
			int fd = list[i].data.fd;
			if(fd == 0){
				char buf[128] = "";
				scanf("%s",buf);
				getchar();
				send(sender,buf,strlen(buf),0);
				continue;
			}

			if(fd == sender){
				char buf[128] = "";
				recv(sender,buf,128,0);
				printf("接收到消息:%s\n",buf);
			}
		}
    }
    return 0;
}