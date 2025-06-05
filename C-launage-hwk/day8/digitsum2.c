#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int digitsum(int n);
int main(int argc, const char *argv[])
{
    char str[128]={0};
    for(;;) {
        printf("请输入一个非负整数：");
        fgets(str,128, stdin);
        str[strcspn(str, "\n")] = '\0';
        if(str[0] == '-')
        {
            printf("请输入正数。\n");
        }
        else if('0' <= str[0] && str[0] <= '9')
        {
            int num = atoi(str);
            printf("各位数字之和：%d\n", digitsum(num));
            break;
        }
        else{printf("您的输入有误。\n");}
    }
    return 0;
} 
int digitsum(int n) {
    if (n < 10) return n;          // 终止条件：个位数直接返回
    return n % 10 + digitsum(n / 10); // 递归：取末位并缩小规模
}