#include <myhead.h>

typedef struct Mylog {
    struct tm s;
    char incident[128];
}mylog;

int num = 0; // 全局变量记录总数

// 函数声明
int mywrite(int total_num);
int myprint(int total_num);
void p_menu();
int load_data();

// 在程序启动时加载数据
int load_data()
{
    FILE* fp = fopen("my.txt", "r");
    if(!fp) {
        num = 0;
        return -1;
    }
    
    num = 0;
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), fp)) {
        num++;
    }
    
    if(num > 0) {
        printf("\n成功加载日志，已有%d条记录。\n", num);
    }
    
    fclose(fp);
    return num;
}

void p_menu()
{
    printf("\n======= 简易记事本 =======\n");
    printf("1.录入日志\n");
    printf("2.查看日志\n");
    printf("3.退出系统\n");
    printf("==========================\n");
}

// 写入文件
int mywrite(int total_num)
{
    FILE* fp = fopen("my.txt", "a");
    if(!fp) {
        ERRLOG("fopen error");
        return total_num;
    }

    int numb;
    printf("请输入事件个数: ");
    scanf("%d", &numb);
    getchar();

    for (int i = 1; i <= numb; i++)
    {
        mylog p;
        time_t t;
        t = time(&t);
	    p.s = *(localtime(&t));
        printf("\n---- 第%d件事时间 ----\n", i);
        
        printf("时间: %02d-%02d-%02d %02d:%02d:%02d\n", p.s.tm_year + 1900, p.s.tm_mon + 1, p.s.tm_mday, p.s.tm_hour + 1, p.s.tm_min + 1, p.s.tm_sec);
        
        printf("事件: ");
        fgets(p.incident, sizeof(p.incident), stdin);
        p.incident[strcspn(p.incident, "\n")] = '\0';
        
        fprintf(fp, "%02d-%02d-%02d-%02d:%02d:%02d %s\n", p.s.tm_year + 1900, p.s.tm_mon + 1, p.s.tm_mday, p.s.tm_hour + 1, p.s.tm_min + 1, p.s.tm_sec, p.incident);
        //printf("%d.%02d-%02d-%02d %02d:%02d:%02d %s\n", total_num + 1, p.s.tm_year + 1900, p.s.tm_mon + 1, p.s.tm_mday, p.s.tm_hour + 1, p.s.tm_min + 1, p.s.tm_sec, p.incident);
        total_num++;
    }

    if(fclose(fp) == EOF) {
        ERRLOG("fclose error");
    }
    
    printf("\n成功录入%d个事件!\n", numb);
    return total_num;
}

// 打印函数
int myprint(int total_num)
{
    if(total_num <= 0) {
        printf("\n记事本为空!\n");
        return -1;
    }
    
    FILE* fp = fopen("my.txt", "r");
    if(!fp) {
        ERRLOG("fopen error");
        return -1;
    }

    printf("\n========== 记事本 (共%d个事件) ==========\n", total_num);
    char date[128], incident[130];
    int count = 0;
    for( ; fscanf(fp, "%s %s", date, incident) == 2; ) {
        count++;
        printf("%d. 时间：%-15s 事件：%s\n", count, date, incident);
    }
    
    if(count != total_num) {
        printf("\n警告：文件记录数(%d)与系统记录数(%d)不一致\n", count, total_num);
    }
    printf("========================================\n");

    fclose(fp);
}

void menu()
{
    int choice;
    for ( ; ; ) {
        p_menu();
        printf("请选择操作: ");
        
        if (scanf("%d", &choice) != 1) {
            getchar();
            printf("输入无效，请重新选择！\n");
            continue;
        }
        getchar(); // 消耗换行符
        
        switch (choice) {
            case 1: 
                num = mywrite(num);  //每次录入更新事件个数
                break;
            case 2: 
                myprint(num); 
                break;
            case 3: 
                printf("已退出\n");
                exit(0);
            default:
                printf("无效选择，请重新输入！\n");
        }
    }
}

int main(int argc, const char *argv[])
{
    // 读取事件数
    load_data();
    
    menu();
    return 0;
}