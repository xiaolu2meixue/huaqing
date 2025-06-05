#include <myhead.h>
void my_input(char* str1, char* str2)
{
    printf("请输入第一个字符串：");
    fgets(str1, 10, stdin);
	printf("请输入第二个字符串：");
    fgets(str2, 10, stdin);
}
void my_cmp(char* buffer1, char* buffer2)
{
	int i;
	for (i = 0; buffer2[i] != '\0'; i++)
	{
		buffer1[i] = buffer2[i];
	}
	buffer1[i] = '\0';
	
}
int main(int argc, const char *argv[])
{
	char buf1[10] = {0};
	char buf2[10] = {0};
	my_input(buf1,buf2);
	my_cmp(buf1, buf2);
	fputs(buf1, stdout);
	fputs(buf2, stdout);
	return 0;
}
