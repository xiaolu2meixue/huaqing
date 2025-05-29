#include <stdio.h>
void shui(int a, int b, int c, int num)
{
    if (num < 100 || num > 999)
	{
        printf("%d 不是三位数\n", num);
        return;
    }
    
    int sum = a*a*a + b*b*b + c*c*c;
    
    if (sum == num) printf("%d 是水仙花数\n", num);
    else printf("%d 不是水仙花数\n", num);
}

int main()
{
    int a, b, c;
    
    printf("请输入三位数的各位数字（空格分隔）：");
    if (scanf("%d %d %d", &a, &b, &c) != 3)
	{
        printf("输入无效！请输入三个整数。\n");
        return 1;
    }
    
    int num = a * 100 + b * 10 + c;
    
    shui(a, b, c, num);
    
    return 0;
}
