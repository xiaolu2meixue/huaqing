#include <myhead.h>
int Str(char* str)
{
	printf("请输入字符串：");
	gets(str);
	int len = strlen(str);
    return len;
}
void copy(char* buf, char* buffer)
{
    int LEN = Str(buf);
    int j = 0;
    for (int i = 0; i < LEN; i++)
    {
        buffer[j] = buf[i];
        j++;
        }
    }
int main(int argc, const char *argv[])
{
    char BUFFER1[100] = {};
    char BUFFER2[100] = {};
    copy(BUFFER1, BUFFER2);
    printf("源字符串为");
    puts (BUFFER1);
    printf("copy后的字符串为");
    puts (BUFFER2);
    return 0;
}