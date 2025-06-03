#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int jitu(int num, int jiao)
{
	int i;
	for(i=1; i <= num; i++)
	{
		if(i * 2 + (num - i) * 4 == jiao) return i;
	}
	return 0;
}
int main(int argc, const char *argv[])
{
	int NUM, JIAO;
	printf("总共多少只头，总共多少只脚");
	if (scanf("%d %d", &NUM, &JIAO) != 2) {
		printf("输入错误！");
		return 1;
	}
	int x = jitu(NUM, JIAO);
	if (x) printf("鸡有%d,兔有%d\n",x, NUM-x);
	else printf("无解\n");
	return 0;
}
