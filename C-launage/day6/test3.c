#include <myhead.h>
int Str(char* str)
{
	printf("请输入字符串：");
	gets(str);
	int len = strlen(str);
    return len;
}
int main(int argc, const char *argv[])
{
	char STR[128] ={};
	int LEN = Str(STR);
	int num = 0;
	for (int i = 0; i < LEN; i++)
	{
		if (STR[i] == ' ') num++;
	}
	printf("该字符串空格个数为：%d\n",num);
	return 0;
}
