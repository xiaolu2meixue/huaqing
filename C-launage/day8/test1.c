#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int yunsuan(int x, char y, int z)
{
	switch (y)
	{
	case '+':printf("%d\n",x+z);break;
	case '-':printf("%d\n",x-z);break;
	case '*':printf("%d\n",x*z);break;
	case '/':printf("%d\n",x/z);break;
	case '%':printf("%d\n",x%z);break;
	default:printf("无此运算\n");

	}
}
int main(int argc, const char *argv[])
{
	int a,c;
	char b;
	scanf("%d %c %d",&a,&b,&c);
	yunsuan(a, b, c);
	return 0;
}
