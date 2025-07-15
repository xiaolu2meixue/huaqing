#include <myhead.h>
#include <poll.h>

void insert_fd(struct pollfd* list, int* list_len, struct pollfd new_fd)
{
    list[*list_len] = new_fd;
    (*list_len)++;
}

void remove_fd(struct pollfd* list, int* list_len, int tar_fd)
{
    for (int i = 0; i < *list_len; i++) {
        if (list[i].fd == tar_fd) {
            for (int j = i; j < *list_len - 1; j++) {
                list[j] = list[j + 1];
            }
            (*list_len)--;
            break;
        }
    }
}

int main(int argc, const char *argv[])
{
    if (argc < 3) {
        printf("用法: %s <ip地址> <端口号>\n", argv[0]);
        return -1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        perror("inet_pton");
        return -1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect");
        return -1;
    }

    printf("已连接到服务器 %s:%s\n", argv[1], argv[2]);

    struct pollfd list[2] = {0};
    int list_len = 0;
    
    struct pollfd poll_stdin = {.fd = 0, .events = POLLIN, .revents = 0};
    struct pollfd poll_sock = {.fd = sock, .events = POLLIN, .revents = 0};
    
    insert_fd(list, &list_len, poll_stdin);
    insert_fd(list, &list_len, poll_sock);

    for (;;) {
        int ret = poll(list, list_len, -1);
        if (ret == -1) {
            perror("poll");
            break;
        }

        for (int i = 0; i < list_len; i++) {
            if (list[i].revents == 0) continue;
            
            if (list[i].fd == 0) {
                char buf[1024] = {0};
                if (fgets(buf, sizeof(buf), stdin) == NULL) {
                    perror("fgets");
                    continue;
                }
                
                buf[strcspn(buf, "\n")] = 0; // 移除换行符
                write(sock, buf, strlen(buf));
            } 
            //检查当前触发事件的文件描述符是否为socket
            else if (list[i].fd == sock) {
                char buf[1024] = {0};
                int res = read(sock, buf, sizeof(buf));
                
                if (res <= 0) {
                    if (res == 0) printf("服务器断开连接\n");
                    else perror("read");
                    close(sock);
                    return 0;
                }
                
                printf("收到消息: %s\n", buf);
            }
        }
    }

    close(sock);
    return 0;
}