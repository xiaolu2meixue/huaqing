#include <myhead.h>
int lenght(char* buffer)
{
	int Len = 0;
	for ( Len = 0; buffer[Len] != '\0'; Len++);
	return Len;
}
int main(int argc, const char *argv[])
{
	char buf[128] = {};
	printf("请输入字符串：");
	fgets(buf, 128, stdin);
	buf[strcspn(buf, "\n")] = '\0'; //buf[strlen(buf)-1] = 0;
	int len = lenght(buf);
	printf("字符串长度为：%d\n",len);
	return 0;
}
