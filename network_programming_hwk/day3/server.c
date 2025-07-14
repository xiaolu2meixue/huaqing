#include <myhead.h>
#include <sys/select.h>

#define MAX_CLIENTS 20   //最大监听20个

void insert_fd(int* client_arr, int* client_arr_len, int new_client)
{
    if (*client_arr_len < MAX_CLIENTS) {
        client_arr[*client_arr_len] = new_client;
        (*client_arr_len)++;
    } else {
        printf("Max clients reached. Cannot accept new connection.\n");
    }
}

void remove_fd(int* client_arr, int* client_arr_len, int tar_client)
{
    for (int i = 0; i < *client_arr_len; i++) {
        if (client_arr[i] == tar_client) {
            for (int j = i; j < *client_arr_len - 1; j++) client_arr[j] = client_arr[j + 1];
            (*client_arr_len)--;
            break;
        }
    }
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        printf("请输入端口号\n");
        return -1;
    }

    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        return -1;
    }

    listen(server, 10);

    fd_set list;
    FD_ZERO(&list);
    FD_SET(server, &list);
    
    int client_arr[MAX_CLIENTS] = {0};
    int client_arr_len = 0;
    int max_fd = server;

    printf("服务器已启动，监听端口 %d\n", ntohs(addr.sin_port));

    for (;;) {
        fd_set backup = list;
        struct timeval tv = {5, 0};

        int ret = select(max_fd + 1, &backup, NULL, NULL, &tv);
        if (ret == -1) {
            perror("select");
            continue;
        }

        if (FD_ISSET(server, &backup)) {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int client = accept(server, (struct sockaddr*)&client_addr, &client_len);
            
            printf("客户端已连接: %s:%d\n", 
                   inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            
            FD_SET(client, &list);
            insert_fd(client_arr, &client_arr_len, client);
            
            if (client > max_fd) {
                max_fd = client;
            }
        }

        for (int i = 0; i < client_arr_len; i++) {
            int client = client_arr[i];
            if (FD_ISSET(client, &backup)) {
                char buf[1024] = {0};
                int res = read(client, buf, sizeof(buf));
                
                if (res == 0) {
                    printf("客户端断开连接\n");
                    close(client);
                    FD_CLR(client, &list);
                    remove_fd(client_arr, &client_arr_len, client);
                    i--; // 调整索引
                }
                else {
                    // 转发消息给所有其他客户端
                    for (int j = 0; j < client_arr_len; j++) {
                        if (client_arr[j] != client) {
                            write(client_arr[j], buf, strlen(buf));
                        }
                    }
                }
            }
        }
    }

    close(server);
    return 0;
}