#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024
#define PORT 8080

// 设置非阻塞模式
static void set_nonblocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }
    
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int server_fd, epoll_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    struct epoll_event ev, events[MAX_EVENTS];
    
    // 创建TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // 绑定socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    // 开始监听
    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port %d\n", PORT);
    
    // 创建epoll实例
    if ((epoll_fd = epoll_create1(0)) == -1) {
        perror("epoll_create1 failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    // 添加服务器socket到epoll
    ev.events = EPOLLIN; // 水平触发(默认模式)
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1) {
        perror("epoll_ctl: server_fd");
        close(server_fd);
        close(epoll_fd);
        exit(EXIT_FAILURE);
    }
    
    for ( ; ; ) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            continue;  // 可继续处理
        }
        
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == server_fd) {
                // 处理新连接
                int new_socket;
                if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                    perror("accept");
                    continue;
                }
                
                printf("New connection from %s:%d\n", 
                       inet_ntoa(address.sin_addr), ntohs(address.sin_port));
                
                // 设置非阻塞模式
                set_nonblocking(new_socket);
                
                // 添加新socket到epoll
                ev.events = EPOLLIN; // 水平触发
                ev.data.fd = new_socket;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &ev) == -1) {
                    perror("epoll_ctl: new_socket");
                    close(new_socket);
                }
            }
            else {
                // 处理客户端数据
                int client_fd = events[i].data.fd;
                char buffer[BUFFER_SIZE];
                
                ssize_t bytes_read = recv(client_fd, buffer, BUFFER_SIZE, 0);
                
                if (bytes_read == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        // 没有数据可读，等待下次通知
                        continue;
                    }
                    else {
                        perror("recv error");
                        close(client_fd);
                        continue;
                    }
                }
                else if (bytes_read == 0) {
                    // 客户端断开连接
                    printf("Client disconnected\n");
                    close(client_fd);
                }
                else {
                    // 回显数据
                    buffer[bytes_read] = '\0'; // 确保字符串终止
                    printf("Received %zd bytes: %s\n", bytes_read, buffer);
                    
                    ssize_t bytes_sent = send(client_fd, buffer, bytes_read, 0);
                    if (bytes_sent == -1) {
                        perror("send error");
                        close(client_fd);
                    }
                    else if (bytes_sent < bytes_read) fprintf(stderr, "Partial write detected (%zd/%zd bytes sent)\n", bytes_sent, bytes_read);
                }
            }
        }
    }
    
    close(server_fd);
    close(epoll_fd);
    return 0;
}