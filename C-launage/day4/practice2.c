#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int prime(int n)
{
	int a;
	for(a = 2; a<n; a++){
		if (n%a == 0) return 1;
	}
	return 0;
}
int main(int argc, const char *argv[])
{
	int N;
	printf("输入一个数字：");
	scanf("%d",&N);
	if(!prime(N)) printf("是质数");
	else printf("不是质数");
	return 0;
}
