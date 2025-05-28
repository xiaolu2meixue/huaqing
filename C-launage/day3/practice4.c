#include <stdio.h>
int xu() 
{
    char c;
        printf("输入一个字符：");
        scanf("%c", &c);
        if (c >= 'A' && c <= 'Z') return c + 32;
        if (c >= 'a' && c < 'z') return c - 32;
        if (c=='z') return c - 57;
        if (c >= '0' && c <= '9') return (c-48)*(c-48);
        else printf("%c\n",c);
}

int main() 
{
    char x = getchar();
    printf(x);
    return 0;
}