#include <myhead.h>

typedef struct Person {
    char name[32];
    char id[16]; 
} person;

int num = 0; // 全局变量记录总人数

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
    num = file_size / sizeof(person);
    
    if(num > 0) {
        printf("\n成功加载名单，已有%d条记录。\n", num);
    }
    
    fclose(fp);
}

void p_menu()
{
    printf("\n==== 简易名单管理系统 ====\n");
    printf("1.录入信息\n");
    printf("2.查看信息\n");
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
    printf("请输入本次录入人数: ");
    scanf("%d", &numb);
    getchar();

    for (int i = 1; i <= numb; i++)
    {
        person p;
        printf("\n--- 录入第%d位成员 ---\n", i);
        
        printf("姓名: ");
        fgets(p.name, sizeof(p.name), stdin);
        p.name[strcspn(p.name, "\n")] = '\0';
        
        printf("ID  : ");
        fgets(p.id, sizeof(p.id), stdin);
        p.id[strcspn(p.id, "\n")] = '\0';
        
        if(fwrite(&p, sizeof(person), 1, fp) != 1) {
            ERRLOG("fwrite error");
            fclose(fp);
            return total_num;
        }
    }

    if(fclose(fp) == EOF) {
        ERRLOG("fclose error");
    }
    
    printf("\n成功录入%d位成员!\n", numb);
    return total_num + numb;
}

// 打印函数
int myprint(int total_num)
{
    if(total_num <= 0) {
        printf("\n通讯录为空!\n");
        return -1;
    }
    
    FILE* fp = fopen("my.txt", "rb");
    if(!fp) {
        ERRLOG("fopen error");
        return -1;
    }

    printf("\n===== 名单成员 (共%d人) =====\n", total_num);
    person new_p;
    for (int i = 0; i < total_num; i++)
    {
        if(fread(&new_p, sizeof(person), 1, fp) != 1) {
            if(feof(fp)) break;     // feof用于检测文件结束
            ERRLOG("fread error");
            break;
        }
        printf("%-2d. %-15s (ID: %s)\n", i+1, new_p.name, new_p.id);
    }
    printf("=============================\n");

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
                num = mywrite(num);
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
    // 读取人数
    load_data();
    
    menu();
    return 0;
}