#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int loop(char* buf)
{
	int i;
	int len = strlen(buf);
	for ( i = 0; i < len; i++)
	{
		printf("%d",buf[i]);
	}
	return 0;

}
int main(int argc, const char *argv[])
{
	char* BUF[10];
	printf("请输入五个数字：");
	scanf("%s",&BUF);
	loop(BUF);
	return 0;
}
