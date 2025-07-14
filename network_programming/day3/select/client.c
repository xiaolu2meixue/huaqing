#include <myhead.h>

int main(int argc, const char *argv[])
{
    if (argc < 2) {
		printf("请输入端口号\n");
		return -1;
	}
	int client = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	short port = atoi(argv[1]);
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr("192.168.139.128"); //inet_addr("0.0.0.0");
	connect(client, (struct sockaddr*)&addr, sizeof(addr));
	//perror("bird");

	for( ; ; ) {
		char buf[128] = "";
		printf("请输入：\n");
		scanf("%s", buf);
		getchar();
		write(client, &buf, sizeof(buf));
	}
	return 0;
}
