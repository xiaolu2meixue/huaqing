#include "myhead.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

#define MAX_MSG_SIZE 256

// 线程函数：接收消息
void* receive_messages(void* arg)
{
    int sockfd = *(int*)arg;
    char buffer[MAX_MSG_SIZE];
    
    while(1)
	{
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        
        if(bytes_received <= 0) 
		{
            if(bytes_received == 0) 
			{
                printf("\n对方已断开连接\n");
            } else 
			{
                perror("接收错误");
            }
            exit(1);
        }
        
        // 清空当前行并显示接收的消息
        printf("对方: %s\n", buffer);
        printf("你: ");
        fflush(stdout); // 立即刷新输出
    }   
    pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
    if(argc < 2)
	{
        printf("用法: %s <端口号> [服务器IP]\n", argv[0]);
        printf("示例: \n");
        printf("  作为服务器: %s 8080\n", argv[0]);
        printf("  作为客户端: %s 8080 127.0.0.1\n", argv[0]);
        return 1;
    }
    //字符转化
    short port = atoi(argv[1]);

    int sockfd;
    
    if(argc == 2) //服务器
	{ 
        // 创建服务器套接字
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == -1) 
		{
            perror("创建套接字失败");
            return 1;
        }
        
        // 设置SO_REUSEADDR选项，避免"地址已在使用"错误
        int reuse = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
		//设置参数
        struct sockaddr_in server_addr = {0};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = inet_addr("0.0.0.0"); // 监听所有网络接口
        
        // 绑定地址
        bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
        // 开始监听
        listen(sockfd, 10);
             
        printf("服务器已启动，等待客户端连接在端口 %d...\n", port);
        
        // 接受客户端连接
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
        
        // 关闭监听套接字（不再需要）
        close(sockfd);
        
        // 获取客户端IP地址
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
        printf("客户端已连接: %s\n", client_ip);
        
        sockfd = client_sock; // 使用客户端套接字进行通信
    } 
	//客户端
    if(argc==3)
	{
        sockfd = socket(AF_INET, SOCK_STREAM, 0);       
        
        struct sockaddr_in server_addr = {0};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = inet_addr(argv[2]); // 连接服务器IP
        
        printf("正在连接服务器 %s:%d...\n", argv[2], port);
        
        // 连接到服务器
        if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)))
		{
            perror("连接失败");
            close(sockfd);
            return 1;
        }
        
        printf("已连接到服务器\n");
    }
    
    // 创建接收消息的线程
    pthread_t recv_thread;
   	if(0!=(errno=pthread_create(&recv_thread, NULL, receive_messages, &sockfd)))
	{
		ERRLOG("pthread_create error");
	}
    // 主线程处理用户输入和发送消息
    char message[MAX_MSG_SIZE];
    
    while(1)
	{
        printf("你: \n");
        fflush(stdout); // 确保提示显示
        
        fgets(message, sizeof(message), stdin);    
        // 移除换行符
        message[strcspn(message, "\n")] = '\0';
 
        // 发送消息
        send(sockfd, message, strlen(message), 0);
       
    }
    
    // 清理
    close(sockfd);
    pthread_cancel(recv_thread); // 终止接收线程
    pthread_join(recv_thread, NULL); // 等待线程结束
    
    printf("程序已退出\n");
    return 0;
}


