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
void cat(char* buf1)
{
    char buf2[128] = {};
    int LEN1 = Str1(buf1);
    int LEN2 = Str2(buf2);
    int j = LEN1;
    
        for (int i = 0; j >= LEN1 && j <= (LEN1 + LEN2); i++)
        {
            buf1[j] = buf2[i];
            j++;
        }
    }
int main(int argc, const char *argv[])
{
    char BUFFER2[100] = {};
    cat(BUFFER2);
    printf("将字符串2cat到字符串1后为：");
    puts (BUFFER2);
    return 0;
}