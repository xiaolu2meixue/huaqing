#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int a,c;
	char b;
	scanf("%d %c %d",&a,&b,&c);
	switch (b)
	{
	case '+':printf("%d\n",a+c);break;
	case '-':printf("%d\n",a-c);break;
	case '*':printf("%d\n",a*c);break;
	case '/':printf("%d\n",a/c);break;
	case '%':printf("%d\n",a%c);break;
	default:printf("无此运算\n");

	}
	return 0;
}
