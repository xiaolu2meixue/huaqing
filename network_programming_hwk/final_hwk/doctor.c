#include <myhead.h>
#include <sqlite3.h>

enum Type {
    TYPE_REGIST,
    TYPE_LOGIN
};

enum Err {
    SUCCESS,
    ERR_NAME,
    ERR_PSWD
};

typedef struct Pack {
    enum Type type;
    enum Err err;
    char name[16];
    char pswd[16];
} pack_t;

// 显示菜单
void show_menu_login() {
    printf("\n************ 病例系统(患者端) ************\n");
    printf("    **            1:注册            **  \n");
    printf("    **            2:登录            **  \n");
    printf("    **            3:退出            **  \n");
    printf("\n****************************************\n");
    printf("请选择:");
    fflush(stdout);
}

void show_menu() {
    printf("\n************ 病例系统(患者端) ************\n");
    printf("    **            1:查询病例            **  \n");
    printf("    **            2:登录            **  \n");
    printf("    **            3:退出            **  \n");
    printf("\n****************************************\n");
    printf("请选择:");
    fflush(stdout);
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        printf("请输入端口号\n");
        return 1;
    }
    
    short port = atoi(argv[1]);
    int client = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (connect(client, (struct sockaddr*)&addr, sizeof(addr))) {
        perror("连接失败");
        return 1;
    }

    fd_set readfds;
    int maxfd = client > 0 ? client : 0;
    
    show_menu_login();
    
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);    // 标准输入
        FD_SET(client, &readfds); // 网络socket
        
        // 等待文件描述符就绪
        int res = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (res < 0) {
            perror("select error");
            break;
        }
        
        // 处理键盘输入
        if (FD_ISSET(0, &readfds)) {
            char choice_buf[16];
            if (fgets(choice_buf, sizeof(choice_buf), stdin) == NULL) {
                printf("读取输入失败\n");
                break;
            }
            
            int ch = atoi(choice_buf);
            pack_t pack = {0};
            
            switch (ch) {
                case 1: 
                case 2: {
                    printf("请输入账号:");
                    fgets(pack.name, sizeof(pack.name), stdin);
                    pack.name[strcspn(pack.name, "\n")] = '\0'; // 移除换行符
                    
                    printf("请输入密码:");
                    fgets(pack.pswd, sizeof(pack.pswd), stdin);
                    pack.pswd[strcspn(pack.pswd, "\n")] = '\0'; // 移除换行符
                    
                    if (ch == 1) pack.type = TYPE_REGIST;
                    if (ch == 2) pack.type = TYPE_LOGIN;
                    write(client, &pack, sizeof(pack));
                    break;
                }
                case 3: exit(0);
                default: {
                    printf("无效选择\n");
                    break;
                }
            }
            show_menu_login();
        }
        
        // 处理网络数据
        if (FD_ISSET(client, &readfds)) {
            pack_t pack;
            int n = read(client, &pack, sizeof(pack));
            if (n <= 0) {
                if (n == 0) {
                    printf("\n服务器断开连接\n");
                }
                else {
                    perror("读取错误");
                }
                break;
            }
            
            // 清空当前行
            printf("\33[2K\r");
            
            switch(pack.type) {
                case TYPE_REGIST: {
                    if(pack.err == SUCCESS) {
                        printf("\n注册成功\n");
                    } else {
                        printf("\n该账号已存在\n");
                    }
                    break;
                }
                case TYPE_LOGIN: {
                    if(pack.err == SUCCESS) {
                        printf("\n登录成功\n");
                    } else if(pack.err == ERR_NAME) {
                        printf("\n该账号不存在\n");
                    } else {
                        printf("\n密码错误\n");
                    }
                    break;
                }
            }
            if(pack.err == SUCCESS) break;
            show_menu_login();
        }
    }
    
    close(client);
    return 0;
}