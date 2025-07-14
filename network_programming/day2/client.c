#include <myhead.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
enum Type {
	TYPE_REGIST,
	TYPE_LOGIN
};

typedef struct Pack {
	int size;
	enum Type type;
	char buf[4096];
	int used;
}pack_t;

void pack_append_data(pack_t* pack, const char* val)
{
	char* buf = pack->buf;
	short len = strlen(val);
	*(short*)(buf + pack->used) = len;
	pack->used += 2;

	strcpy(buf + pack->used, val);
	pack->used += len;

	pack->size = 8 + pack->used;
}
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
	addr.sin_addr.s_addr = inet_addr("192.168.127.87"); //inet_addr("0.0.0.0");
	connect(client, (struct sockaddr*)&addr, sizeof(addr));
	//perror("bird");

	for( ; ; ) {
		char name[16] = "";
		char pswd[16] = "";

		printf("请输入账号：%s\n", name);
        scanf("%s", name);
		getchar();

		printf("请输入账号：%s\n", name);
        scanf("%s", name);
		getchar();

		pack_t pack = {0};
		pack_append_data(&pack, name);
		pack_append_data(&pack, pswd);
        write(client, &pack, 4 + pack.used);
	}
	return 0;
}
