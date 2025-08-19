#include <myhead.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#define MAX_EVENTS 20

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        printf("请输入端口号\n");
        return -1;
    }

    // 创建服务器socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == -1) {
        perror("socket");
        return -1;
    }

    // 设置服务器地址
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    short port = atoi(argv[1]);
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY; // 比0更清晰

    // 设置socket选项，避免地址占用
    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(server, (struct sockaddr*)&addr, sizeof(addr))) {
        perror("bind");
        close(server);
        return -1;
    }

    if (listen(server, 10)) {
        perror("listen");
        close(server);
        return -1;
    }

    // 创建epoll实例
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd == -1) {
        perror("epoll_create1");
        close(server);
        return -1;
    }

    // 添加服务器socket和标准输入到epoll
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = server;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, server, &ev) == -1) {
        perror("epoll_ctl: server");
        close(server);
        close(epfd);
        return -1;
    }

    ev.data.fd = STDIN_FILENO; // 标准输入
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) == -1) {
        perror("epoll_ctl: stdin");
        close(server);
        close(epfd);
        return -1;
    }

    struct epoll_event events[MAX_EVENTS];
    
    while (1) {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < nfds; ++i) {
            int fd = events[i].data.fd;

            if (fd == STDIN_FILENO) {
                // 处理标准输入
                char buf[128] = "";
                if (fgets(buf, sizeof(buf), stdin)) {
                    buf[strcspn(buf, "\n")] = 0; // 移除换行符
                    printf("键盘输入了：%s\n", buf);
                }
            } 
            else if (fd == server) {
                // 处理新连接
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client = accept(server, (struct sockaddr*)&client_addr, &client_len);
                if (client == -1) {
                    perror("accept");
                    continue;
                }

                printf("客户端已连接: %s:%d\n", 
                      inet_ntoa(client_addr.sin_addr), 
                      ntohs(client_addr.sin_port));

                // 设置非阻塞模式
                int flags = fcntl(client, F_GETFL, 0);
                fcntl(client, F_SETFL, flags | O_NONBLOCK);

                // 添加新客户端到epoll
                ev.events = EPOLLIN | EPOLLET; // 边缘触发模式
                ev.data.fd = client;
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, client, &ev) == -1) {
                    perror("epoll_ctl: client");
                    close(client);
                }
            } 
            else {
                // 处理客户端数据
                char buf[1024] = {0};
                ssize_t res = read(fd, buf, sizeof(buf)-1);
                
                if (res <= 0) {
                    // 客户端断开连接
                    if (res == 0) {
                        printf("客户端断开连接\n");
                    } else {
                        perror("read");
                    }
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                } else {
                    buf[res] = '\0';
                    printf("客户端发来消息：%s\n", buf);
                }
            }
        }
    }

    close(server);
    close(epfd);
    return 0;
}