#include <myhead.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <sys/epoll.h>

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
	
    int epfd = epoll_create(EPOLL_CLOEXEC);

	//准备一下想要监视的文件描述符
	struct epoll_event epoll_stdin = {.events = EPOLLIN, data : { fd : 0}};
	struct epoll_event epoll_server = {.events = EPOLLIN, data : { fd : server}};
    // epoll_ctl函数：参数：
    // epfd: epoll 实例的文件描述符
    // op: 操作类型
    //     EPOLL_CTL_ADD: 添加新的 fd
    //     EPOLL_CTL_MOD: 修改已存在的 fd
    //     EPOLL_CTL_DEL: 删除 fd
    // fd: 要操作的目标文件描述符
    // event: 事件结构体指针
    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &epoll_stdin);
    epoll_ctl(epfd, EPOLL_CTL_ADD, server, &epoll_server);
    int eplen = 2;

    for( ; ; ) {
        struct epoll_event list[20] = {0};
        //epoll_wait函数：
        // 参数：
        // epfd: epoll 实例的文件描述符
        // events: 用于返回就绪事件的数组
        // maxevents: 最多返回的事件数量
        // timeout: 超时时间（毫秒），-1 表示无限等待
        // 返回值:成功时:返回 就绪的文件描述符数量（即有多少个 fd 有事件发生）
        //             返回 0 表示超时时间内没有事件发生
        //       失败时:返回 -1，并设置 errno 为相应的错误码
        int count = epoll_wait(epfd, list, eplen, -1);
            for(int i = 0; i < count; i++) {
                int fd = list[i].data.fd;

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
			    struct epoll_event epoll_client = {.events = EPOLLIN , .data.fd = client};
                epoll_ctl(epfd, EPOLL_CTL_ADD, client, &epoll_client);
                eplen++;
                continue;
            }

            char buf[1024] = {};
            int res = read(fd, buf, 1024);
		    if (res == 0) {
                printf("客户端断开连接\n");
                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                continue;
            }
		    printf("客户端发来消息：%s\n", buf);
            }
	}
	return 0;
}
