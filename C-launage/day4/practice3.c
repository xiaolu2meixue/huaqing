#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int Fibonacci(int n)
{
	int a = 1,b = 1, c = 2, i;
	for(i=0; i<=n; i++){
		printf(" %d", a);
		c = a + b;
		a = b;
		b = c;
	}
	printf("\n");
	return 0;
}
int main(int argc, const char *argv[])
{
	int N;
	printf("请输入位数：");
	scanf("%d",&N);
	Fibonacci(N);
	return 0;
}
