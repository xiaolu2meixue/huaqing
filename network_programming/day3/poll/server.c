#include <myhead.h>
#include <sys/select.h>
#include <sys/poll.h>

void insert_fd(struct pollfd* list, int* list_len, struct pollfd new_fd)
{
	list[*list_len] = new_fd;
	(*list_len)++;
}

void remove_fd(struct pollfd* list, int* list_len, int tar_fd)
{
	int i = 0, j = 0, len = *list_len;
	for ( i = 0; i < len; i++) if (list[i].fd == tar_fd) break;
    if (i == len) return;
	for ( j = i; j < len - 1; j++) list[j] = list[j + 1];
	(*list_len)--;
	
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
	short port = atoi(argv[1]);
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = 0; //inet_addr("0.0.0.0");
	if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) == -1) perror("bind");

	listen(server, 10);

	struct pollfd list[20] = {0};    //准备一个poll模型的监视列表
	int list_len = 0;
	
	//准备一下想要监视的文件描述符
	struct pollfd poll_stdin = {.fd = 0, .events = POLLIN, .revents = 0};
	struct pollfd poll_server = {.fd = server, .events = POLLIN, .revents = 0};

    insert_fd(list, &list_len, poll_stdin);
    insert_fd(list, &list_len, poll_server);

    for( ; ; ) {
        poll(list, list_len, -1);
            for(int i = 0; i < list_len; i++) {
		    if (list[i].revents == 0) continue;   //如果当前描述符revents是0，说明没激活，直接continue查看下一个描述符
            int fd =list[i].fd;

            if (fd == 0) {
			    char buf[128] = "";
			    scanf("%s", buf);
			    getchar();
			    printf("键盘输入了：%s\n", buf);
                continue;
		    }

            if (fd == server) {
			    struct sockaddr_in client_addr;
			    int client_len = sizeof(client_addr);
			    int client = accept(server, (struct sockaddr*)&client_addr, &client_len);
			    printf("客户端已连接: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			    struct pollfd poll_new_client = {.fd = client, .events = POLLIN, .revents = 0};
                insert_fd(list, &list_len, poll_new_client);
                continue;
            }

            char buf[1024] = {};
            int res = read(fd, buf, 1024);
		    if (res == 0) {
                printf("客户端断开连接\n");
                remove_fd(list, &list_len, fd);
                continue;
            }
		    printf("客户端发来消息：%s\n", buf);
            }
	}
	return 0;
}
