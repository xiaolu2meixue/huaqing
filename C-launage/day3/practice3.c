#include <stdio.h>
int ascending()
{
    char a,b;
    while (1) 
    {
        int t;
        printf("输入2个数字");
        scanf(" %d %d", &a,b);
        if (a>b) return t=a,a=b,b=t;
        else if(a<b) return a,b;
        else printf("错误：需输入2个不同数字，请重试！\n");
    }
}

int main() 
{
    char x = ascending();
    printf("%c\n", x);
    return 0;
}