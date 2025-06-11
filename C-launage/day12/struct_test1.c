#include <myhead.h>
typedef struct employee {
    int id;
    char* name;
    int sex;
} employee;
employee* init_emps(int *count)
{
    printf("请输入员工个数：");
    scanf("%d", count);
    getchar();
    employee *emp = (employee*)malloc(*count * sizeof(employee));
    for (int i = 0; i < *count; i++) {
        emp[i].id = i;
        printf("请输入第%d个员工姓名：", i + 1);
        emp[i].name = (char*)malloc(sizeof(char) * 20);
        fgets(emp[i].name, 20, stdin);
        size_t len = strlen(emp[i].name);
        if (len > 0 && emp[i].name[len-1] == '\n') {
            emp[i].name[len-1] = '\0';
        }
        printf("请输入第%d个员工姓别：", i + 1);
        scanf("%d", &emp[i].sex);
        getchar();
    }
    return emp;
}
void printf_emps(employee *member, int members)
{
    printf("ID\t\t姓名\t\t性别\n");
    printf("==========================================\n");
    for (int i = 0; i < members; i++) {
        printf("%d\t\t", member[i].id);
        printf("%s\t\t", member[i].name);
        printf("%s\t\t", member[i].sex ? "男" : "女");
        printf("\n");
    }
    
}
int main(int argc, const char *argv[])
{
    int count = 0;
    // 调用输入函数
    employee *emps = init_emps(&count);
    // 调用打印函数
    printf_emps(emps, count);
    // 释放内存
    for (int i = 0; i < count; i++) free(emps[i].name);
    free(emps);
    emps = NULL;
    return 0;
}