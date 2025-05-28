#include <stdio.h>
int main() 
{
    int a;
    scanf("%d",&a);
    a%4!=0 || a%100==0||a%400!=0?printf("不是闰年"):printf("闰年");
}
