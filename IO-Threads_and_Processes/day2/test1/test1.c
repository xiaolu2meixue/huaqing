#include <myhead.h>

typedef struct Mylog {
    char date[15];
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
    FILE* fp = fopen("my.txt", "rb");
    if(!fp) {
        num = 0;
        return -1;
    }
    
    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    // 计算记录数
    num = file_size / sizeof(mylog);
    
    if(num > 0) {
        printf("\n成功加载日志，已有%d条记录。\n", num);
    }
    
    fclose(fp);
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
    FILE* fp = fopen("my.txt", "ab");
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
        printf("\n--- 录入第%d件事时间 ---\n", i);
        
        printf("时间: ");
        fgets(p.date, sizeof(p.date), stdin);
        p.date[strcspn(p.date, "\n")] = '\0';
        
        printf("事件: ");
        fgets(p.incident, sizeof(p.incident), stdin);
        p.incident[strcspn(p.incident, "\n")] = '\0';
        
        if(fwrite(&p, sizeof(mylog), 1, fp) != 1) {
            ERRLOG("fwrite error");
            fclose(fp);
            return total_num;
        }
    }

    if(fclose(fp) == EOF) {
        ERRLOG("fclose error");
    }
    
    printf("\n成功录入%d个事件!\n", numb);
    return total_num + numb;
}

// 打印函数
int myprint(int total_num)
{
    if(total_num <= 0) {
        printf("\n记事本为空!\n");
        return -1;
    }
    
    FILE* fp = fopen("my.txt", "rb");
    if(!fp) {
        ERRLOG("fopen error");
        return -1;
    }

    printf("\n===== 记事本 (共%d个事件) =====\n", total_num);
    mylog new_p;
    for (int i = 0; i < total_num; i++)
    {
        if(fread(&new_p, sizeof(mylog), 1, fp) != 1) {
            if(feof(fp)) break;     // feof用于检测文件结束
            ERRLOG("fread error");
            break;
        }
        printf("时间：%-4s. 事件：%-15s \n", new_p.date, new_p.incident);
    }
    printf("==============================\n");

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