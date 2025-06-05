#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int m = 0;
void digitsum(int n)
{
	m += n%10;
    n /= 10;
    if(n%10 == 0) {
        printf("%d\n", m);
        return;
    }
	else digitsum(n);
}
int main(int argc, const char *argv[])
{
	int num;
	
    // for (num = -1; num < 0;)
    // {
        printf("请输入数字：");
	    scanf("%d",&num);
        printf("%d",num);
        //if(num >= 0) break;
        printf("请输入正整数！\n");
    //}
	digitsum(num);
	return 0;
}