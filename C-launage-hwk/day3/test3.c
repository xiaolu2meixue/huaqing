#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int n;
	scanf("%d",&n);
	if(0==n%3&0==n%5&&0==n%7) printf("3 5 7\n");
	else if(0==n%3&&0==n%5) printf("3 5\n");
	else if(0==n%5&&0==n%7) printf("5 7\n");
	else if(0==n%3&&0==n%7) printf("3 7\n");
	else if(0==n%3) printf("3\n");
	else if(0==n%5) printf("5\n");
	else if(0==n%7) printf("7\n");
	else printf("%d\n",n);
	return 0;
}
