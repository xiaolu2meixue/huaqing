#include <stdio.h>

// 判断是否大写字母 (A-Z)
int is_BIG(char c)
{
    return (c >= 'A' && c <= 'Z');
}

int is_SMALL(char c)
{
    return (c >= 'a' && c <= 'z');
}

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

char to_SMALL(char c)
{
    if (is_BIG(c))
    {
        return c + ('a' - 'A');
    }
    return c;
}

char to_BIG(char c) {
    if (is_SMALL(c))
    {
        return c - ('a' - 'A');
    }
    return c;
}

void handle_BIG(char c)
{
    if (is_BIG(c))
    {
        printf("输出结果: %c\n", to_SMALL(c));
    }
}

void handle_SMALL(char c)
{
    if (is_SMALL(c))
    {
        printf("输出结果: %c\n", to_BIG(c));
    }
}

void handle_digit(char c)
{
    if (is_digit(c))
    {
        int num = c - '0';
        printf("平方: %d\n", num * num);
    }
}

void handle_other(char c) {
    if (!is_BIG(c) && !is_SMALL(c) && !is_digit(c)) {
        printf("输出结果: %c\n", c);
    }
}

int main() {
    char input;
    
    printf("请输入: ");
    scanf("%c", &input);
    
    handle_BIG(input);
    handle_SMALL(input);
    handle_digit(input);
    handle_other(input);
    
    return 0;
}