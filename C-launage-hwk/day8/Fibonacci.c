#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int a = 1,b = 1, c = 2;
void Fibonacci(int m)
{
	printf(" %d", a);
	c = a + b;
	a = b;
	b = c;
    if(m == 1) {
        printf("\n");
        return;
    }
	else Fibonacci(m-1);
}
int main(int argc, const char *argv[])
{
	int n;
	printf("请输入位数：");
	scanf("%d",&n);
	Fibonacci(n);
	return 0;
}