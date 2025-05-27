#include<stdio.h>
#include<string.h>
#define change(a,b) t=a,a=b,b=t;
int main(int argc, const char *argv[])
{
	int a,b,t;
	scanf("%d %d",&a,&b);
	change(a,b);
	printf("%d %d\n",a,b);
	return 0;
}
