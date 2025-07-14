#include <myhead.h>
#include <sys/select.h>

void insert_client(int* client_arr, int* client_arr_len, int new_client)
{
	client_arr[*client_arr_len] = new_client;
	(*client_arr_len)++;
}

void remove_client(int* client_arr, int* client_arr_len, int tar_client)
{
	int i = 0, j = 0;
	int len = *client_arr_len;
	for ( i = 0; i < len; i++) if (client_arr[i] == tar_client) break;
	for ( j = i; j < len - 1; j++) client_arr[j] = client_arr[j + 1];
	client_arr[j] = -1;
	(*client_arr_len)--;
	
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

	fd_set list;    //准备一个select模型的监视列表
	FD_ZERO(&list);
	int client_arr[10] = {0};
	int client_arr_len = 0;

	struct timeval tv;
	int fd_count = 3;  //因为当前程序中，有文件描述符 0 1 2 server(3)
	
	//监视标准输入流和服务器套接字
	FD_SET(0, &list);
	FD_SET(server, &list);
	

	tv.tv_sec = 5;
    tv.tv_usec = 0;

    for( ; ; ) {
		//list是监视列表，backup是激活列表
		fd_set backup = list;
		select(fd_count + 1, &backup, NULL, NULL, &tv);

		if (FD_ISSET(server, &backup)) {
			struct sockaddr_in client_addr;
			int client_len = sizeof(client_addr);
			int client = accept(server, (struct sockaddr*)&client_addr, &client_len);
			printf("客户端已连接: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			fd_count = client;
			FD_SET(client,&list);
			insert_client(client_arr, &client_arr_len, client);
		}

		if (FD_ISSET(0, &backup)) {
			char buf[128] = "";
			scanf("%s", buf);
			getchar();
			printf("键盘输入了：%s\n", buf);
		}

		for (int i = 0; i < client_arr_len; i++) {
			int client = client_arr[i];
			if (FD_ISSET(client, &backup)) {
				char buf[128] = {};
				int res = read(client, buf, 128);
				if (res == 0) {
					printf("客户端断开连接\n");

					//从监视列表中移除该客户端
					FD_CLR(client, &backup);

					//从管理客户端数据中移除该客户端
					remove_client(client_arr, &client_arr_len, client);
					continue;
				}
			printf("客户端发来消息：%s\n", buf);	
			}
			
		}
		
	}
	return 0;
}
