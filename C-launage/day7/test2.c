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
int cmp()
{
    char buf1[128] = "";
    char buf2[128] = "";
    int LEN1 = Str1(buf1), LEN2 = Str2(buf2);
    int LEN = 0, i;
    if(LEN1 >= LEN2) LEN = LEN2;
    else LEN = LEN1;
    for (i = 0; i <= LEN; i++)
    {
        if(buf1[i] != buf2[i]) break;
    }
    int sub = buf1[i] -buf2[i];
    return sub;
}
int main(int argc, const char *argv[])
{
    int SUB = cmp();
    printf("%d\n",SUB);
    return 0;
}
