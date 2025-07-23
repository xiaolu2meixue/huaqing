#include <myhead.h>
#include <sqlite3.h>

enum Type {
    TYPE_PAT_REGIST,         // 病人注册
    TYPE_PAT_LOGIN,          // 病人登录
    TYPE_PATIENT_QUERY_CASE   // 病人查询病例
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

// 病例记录结构
typedef struct CaseRecord {
    char date[20];          // 日期时间
    char doctor[16];        // 接诊医生
    char patient_desc[256]; // 病人口述
    char diagnosis[256];    // 医生诊断
    char prescription[256]; // 医生开药
    char advice[256];       // 医生医嘱
} case_record_t;

// 显示登录菜单
void show_menu_login() {
    printf("\n************ 病例系统(患者端) ************\n");
    printf("    **            1:注册            **  \n");
    printf("    **            2:登录            **  \n");
    printf("    **            3:退出            **  \n");
    printf("\n****************************************\n");
    printf("请选择:");
    fflush(stdout);
}

// 显示病人主菜单
void show_patient_menu() {
    printf("\n************ 病例系统(患者端) ************\n");
    printf("    **        1:查询我的病例        **  \n");
    printf("    **        2:退出                **  \n");
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
    char patient_name[16] = {0}; // 保存登录的病人名
    int last_request_type = 0;   // 记录最后请求类型

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        FD_SET(client, &readfds);
        
        int res = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (res < 0) {
            perror("select error");
            break;
        }
        
        if (FD_ISSET(0, &readfds)) {
            char choice_buf[16];
            if (fgets(choice_buf, sizeof(choice_buf), stdin) == NULL) {
                printf("读取输入失败\n");
                break;
            }
            
            int ch = atoi(choice_buf);
            
            // 未登录状态
            if (patient_name[0] == '\0') {
                pack_t pack = {0};
                switch (ch) {
                    case 1: 
                    case 2: {
                        printf("请输入账号:");
                        fgets(pack.name, sizeof(pack.name), stdin);
                        pack.name[strcspn(pack.name, "\n")] = '\0';
                        
                        printf("请输入密码:");
                        fgets(pack.pswd, sizeof(pack.pswd), stdin);
                        pack.pswd[strcspn(pack.pswd, "\n")] = '\0';
                        
                        if (ch == 1) pack.type = TYPE_PAT_REGIST;
                        if (ch == 2) pack.type = TYPE_PAT_LOGIN;
                        write(client, &pack, sizeof(pack));
                        break;
                    }
                    case 3: 
                        close(client);
                        exit(0);
                    default: {
                        printf("无效选择\n");
                        break;
                    }
                }
            } 
            // 已登录状态
            else {
                switch(ch) {
                    case 1: { // 查询我的病例
                        enum Type type = TYPE_PATIENT_QUERY_CASE;
                        write(client, &type, sizeof(enum Type));
                        last_request_type = 1;
                        break;
                    }
                    case 2: 
                        close(client);
                        exit(0);
                    default:
                        printf("无效选择\n");
                }
            }
            
            // 更新菜单显示
            if (patient_name[0]) {
                show_patient_menu();
            } else {
                show_menu_login();
            }
        }
        
        if (FD_ISSET(client, &readfds)) {
            if (last_request_type == 1) { // 处理查询响应
                int count;
                read(client, &count, sizeof(int));
                
                if (count == 0) {
                    printf("没有找到您的病例记录\n");
                } else {
                    printf("\n===== 您的病例记录(%d条) =====\n", count);
                    for (int i = 0; i < count; i++) {
                        case_record_t record;
                        read(client, &record, sizeof(case_record_t));
                        
                        printf("\n记录 %d:\n", i+1);
                        printf("日期: %s\n", record.date);
                        printf("接诊医生: %s\n", record.doctor);
                        printf("病人口述: %s\n", record.patient_desc);
                        printf("医生诊断: %s\n", record.diagnosis);
                        printf("医生开药: %s\n", record.prescription);
                        printf("医生医嘱: %s\n", record.advice);
                    }
                    printf("===============================\n");
                }
                last_request_type = 0;
            } 
            else { // 登录/注册响应
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
                
                printf("\33[2K\r");
                
                switch(pack.type) {
                    case TYPE_PAT_REGIST: {
                        if(pack.err == SUCCESS) {
                            printf("\n注册成功\n");
                        } else {
                            printf("\n该账号已存在\n");
                        }
                        break;
                    }
                    case TYPE_PAT_LOGIN: {
                        if(pack.err == SUCCESS) {
                            printf("\n登录成功\n");
                            strcpy(patient_name, pack.name);
                            printf("*************** 患者%s你好 **************\n", patient_name);
                            show_patient_menu();
                        } else if(pack.err == ERR_NAME) {
                            printf("\n该账号不存在\n");
                        } else {
                            printf("\n密码错误\n");
                        }
                        break;
                    }
                }
                if (pack.type == TYPE_PAT_LOGIN && pack.err != SUCCESS) {
                    show_menu_login();
                }
            }
        }
    }
    
    close(client);
    return 0;
}