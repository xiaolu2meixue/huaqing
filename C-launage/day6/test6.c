#include <myhead.h>
int Str1(char* str1)
{
	printf("请输入字符串：");
	gets(str1);
	int len1 = strlen(str1);
    return len1;
}
int Str2(char* str2)
{
	printf("请输入字符串：");
	gets(str2);
	int len2 = strlen(str2);
    return len2;
}
int change(char* buf1, char* buf2)
{
    Str1(buf1);
    Str2(buf2);
    char buf3[128] ={};
    strcpy(buf3,buf1);strcpy(buf1,buf2);strcpy(buf2,buf3);
}
int main(int argc, const char *argv[])
{
    int buffer1[128] = {};
    int buffer2[128] = {};
	change(buffer1, buffer2);
    puts(buffer1);
    puts(buffer2);
	return 0;
}