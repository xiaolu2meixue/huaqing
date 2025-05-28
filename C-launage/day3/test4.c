#include <stdio.h>
int max_min() 
{
    char c;
    while (1) 
    {
        printf("输入一个大写字母：");
        scanf(" %c", &c);
        if (c >= 'A' && c <= 'Z') return c + 32;
        else printf("错误：需输入大写字母（A-Z），请重试！\n");
    }
}

int main() 
{
    char x = max_min();
    printf("转换结果：%c\n", x);
    return 0;
}