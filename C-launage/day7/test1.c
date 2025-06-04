#include <myhead.h>
int Str1(char* str1)
{
	printf("请输入字符串1：");
	gets(str1);
	int len1 = strlen(str1);
    return len1;
}
int Str2(char* str2)
{
	printf("请输入字符串2：");
	gets(str2);
	int len2 = strlen(str2);
    return len2;
}
int Str3(char* str3)
{
	printf("请输入字符串3：");
	gets(str3);
	int len3 = strlen(str3);
    return len3;
}
void cmp(char* max)
{
    char buf1[128] = "";
    char buf2[128] = "";
    char buf3[128] = "";
    int LEN1 = Str1(buf1), LEN2 = Str2(buf2), LEN3 = Str3(buf3);
    if (strcmp(buf1, buf2) >= 0) strcpy(max, buf1);
    else strcpy(max, buf2);
    if (strcmp(max,buf3) >=0) return;
    else strcpy(max, buf3);
}
int main(int argc, const char *argv[])
{
    char BUFFER[128] = "";
    cmp(BUFFER);
    puts (BUFFER);
    return 0;
}