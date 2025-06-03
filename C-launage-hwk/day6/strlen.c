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
	char buf[128]={};
	Str(buf);
	size_t i;
	for(i=0; buf [i]; ++i);
	printf("%ld\n", i);
	return 0;
}
