#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int output_perfect(int num)
{
	int n;
	int sum = 0;
	for (n=num - 1; n>0; n--)
	{
		if (num%n == 0) sum += n;
	}
	return sum;
}
int main(int argc, const char *argv[])
{
	int NUM, SUM;
	printf("请输入数字：\n");
	if (scanf(" %d", &NUM )!= 1){
		printf("输入错误");
		return 1;
	}
    SUM = output_perfect(NUM);
	if (NUM == SUM) printf("是完美数\n");
	else printf("不是完美数\n");
	return 0;
}
