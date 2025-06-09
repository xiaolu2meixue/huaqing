#include <myhead.h>
int Str1(char* str1)
{
	printf("请输入字符串1：");
	fgets(str1, 10, stdin);
    str1[strcspn(str1, "\n")] = '\0';
	int len1 = strlen(str1);
    return len1;
}
int Str2(char* str2)
{
	printf("请输入字符串2：");
	fgets(str2, 10, stdin);
    str2[strcspn(str2, "\n")] = '\0';
	int len2 = strlen(str2);
    return len2;
}
int cmp()
{
    char* buf1 = (char*)malloc(sizeof(char) * 10);
    char* buf2 = (char*)malloc(sizeof(char) * 10);
    int LEN1 = Str1(buf1), LEN2 = Str2(buf2);
    int LEN = 0, i;
    char* buffer1 = buf1;
    char* buffer2 = buf2;
    if(LEN1 >= LEN2) LEN = LEN2;
    else LEN = LEN1;
    for (i = 0; i <= LEN; i++,buffer1++, buffer2++) {
        if(*buffer1 != *buffer2) break;
    }
    int sub = *buffer1 - *buffer2;
    free(buf1);
    free(buf2);
    buf1 = NULL;
    buf2 = NULL;
    return sub;
}
int main(int argc, const char *argv[])
{
    int SUB = cmp();
    printf("%d\n",SUB);
    return 0;
}