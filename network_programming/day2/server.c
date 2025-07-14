#include <myhead.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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

void read_data_from_pack(pack_t* pack, int packsize)
{
    char* buf = pack->buf;
	char** list = (char**)calloc(20, );
    for ( ; ; ) {
        short size = *(short*)buf;

        char temp[size + 1];
        memset(temp, 0 , size + 1);
        strcpy(temp, buf + 2);

        memmove(buf, buf + 2 +size, packsize - 2 - size - 8);
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
	short port = atoi(argv[1]);
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = 0; //inet_addr("0.0.0.0");
	if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) == -1) perror("bird");

	listen(server, 10);
	printf("服务器启动，等待客户端连接...\n");
	struct sockaddr_in client_addr;
	int client_len = sizeof(client_addr);
	int client = accept(server, (struct sockaddr*)&client_addr, &client_len);
	
	printf("客户端已连接: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    for( ; ; ) {
		int size = 0;
		int res = read(client, &size, 4);
		if (res ==0) {
			printf("客户端断开链接\n");
			return 0;
		}
		pack_t pack = {0};
		pack.size = size;
		res = read(client, (char*)&pack + 4, size - 4);
	}
	return 0;
}
