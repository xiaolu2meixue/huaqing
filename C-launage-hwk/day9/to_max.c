#include <myhead.h>
#define MAX_NUM 10

typedef struct employee {
    int id;
    char name[15];
    int sex;
}employee;

int input_str(employee* str)
{
    int count = 0;
    for (int i = 0; i < MAX_NUM; i++) {
        printf("请输入字符: ");
        fgets(str[i].name, 15, stdin);
        str[i].name[strcspn(str[i].name, "\n")] = '\0';  // 移除换行符
        if (*str[i].name == '#') return count;
        count++;
    } 
}
int to_max(employee* str,int rel_len)
{
    for (int i = 0; i < rel_len - 1; i++)
    {
        if (i%2 == 0) {
            if (*str[i].name >= 'a' && *str[i].name <= 'z') {
                *str[i].name = *str[i].name - 32;
            }
        }
    }
    
}
int main(int argc, const char *argv[])
{
    employee* employee_str = (employee*)malloc(sizeof(employee) * MAX_NUM);
    int len = input_str(employee_str);
    to_max(employee_str, len);

    for(int i = 0; i <= len - 1; i++) printf("employee_str[%d].name = %s\n", i, employee_str[i].name);

    free (employee_str);
    employee_str = NULL;
	return 0;
}