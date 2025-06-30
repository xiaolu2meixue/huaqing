#include <myhead.h>

typedef struct Person {
	char name[15];
	char id[5];
}person;

int num = 0;

//menu函数
void p_menu()
{
    printf("1.录入信息\n");
    printf("2.查看信息\n");
    printf("3.退出系统\n");
}
//写入文件
int mywrite()
{
    //打开文件
	FILE* fp = fopen("my.txt", "ab");
	if(!fp) {
		ERRLOG("fopen error");
		return -1;
	}

    //写入文件
    int numb;
    printf("请输入人数");
    scanf("%d", &numb);
    getchar();
    num += numb;
    for (int i = 1; i <= numb; i++)
    {
        person p;
        printf("请输入第%d个成员姓名：", i);
        fgets(p.name, sizeof(person), stdin);
        p.name[strcspn(p.name, "\n")] = '\0';
        printf("请输入第%d个成员id：", i);
        fgets(p.id, sizeof(person), stdin);
        p.id[strcspn(p.id, "\n")] = '\0';
        
        size_t written = fwrite(&p, sizeof(person), 1, fp);
        if(written != 1) {
            ERRLOG("fwrite error");
            fclose(fp);
            return -1;
        }
    }
    return num;

    //关闭写入的文件
	if(EOF == fclose(fp)) {
		ERRLOG("fclose error");
	}
}

//打印函数
int myprint()
{
    FILE* fp = fopen("my.txt", "rb");
    for (int i = 1; i <= num; i++) {
        //读取文件
	    person new_p;
	    fread(&new_p, sizeof(person), 1, fp);
	    printf("Name: %s, ID: %s\n", new_p.name, new_p.id);
    }
    // 关闭读取的文件
    if (fclose(fp) != 0) {
        ERRLOG("fclose error");
        return -1;
    }
    
}

void menu(int num)
{
    int choice;
    for ( ; ; ) {
        p_menu();
        printf("请选择操作: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // 清空无效输入
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
    menu(num);
	return 0;
}
