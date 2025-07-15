#include <myhead.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct sockaddr_in addr_in_t;
typedef struct sockaddr addr_t;
typedef struct sockaddr_un addr_un_t;

int main(int argc, const char *argv[])
{
    if(argc < 2){
        printf("请输入端口号\n");
        return 1;
    }
    
    short port = atoi(argv[1]);
    
    int reciver = socket(AF_INET,SOCK_DGRAM,0);

    int optval = 1;
    if (setsockopt(reciver, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))) {
        perror("setsockopt error");
        close(reciver);
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    addr.sin_port = htons(port);
    
    if(bind(reciver,(struct sockaddr*)&addr,sizeof(addr)) == -1){
        perror("bind");
        return 1;
    }
    
    while(1){
        char buf[128] = "";
        read(reciver,buf,128);
        printf("读取到udp消息:%s\n",buf);
    }
    return 0;
}