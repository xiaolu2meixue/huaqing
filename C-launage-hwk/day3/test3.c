#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int n;
	scanf("%d",&n);
	if(0==n%3) printf("3 ");
	if(0==n%5) printf("5 ");
	if(0==n%7) printf("7\n");
	else printf("%d\n",n);
	return 0;
}
