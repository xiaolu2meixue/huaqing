#include <myhead.h>
int Str(char* str)
{
	printf("请输入字符串：");
	gets(str);
	int len = strlen(str);
    return len;
}
void del(char* buffer)
{
    char buf[100] = {};
    int LEN = Str(buf);
    int j = 0;
    for (int i = 0; i < LEN; i++)
    {
        if (buf[i] == ' ') {
            continue;
        }
        buffer[j] = buf[i];
        j++;
        }
    }
int main(int argc, const char *argv[])
{
    char BUFFER[100] = {};
    del(BUFFER);
    puts (BUFFER);
    return 0;
}