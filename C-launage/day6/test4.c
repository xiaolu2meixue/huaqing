#include <myhead.h>
int Str(char* str)
{
	printf("请输入字符串：");
	gets(str);
	int len = strlen(str);
    return len;
}
void invert(char* buf)
{
    int LEN = Str(buf);
	char* left = buf;
    char* right = buf + LEN - 1;
	for (int i = 0; i <= LEN/2; i++)
    {
        int t = *left; *left = *right; *right = t;
        left++;
        right--;
    }
}
int main(int argc, const char *argv[])
{
    char buffer[100] = {};
    invert(buffer);
    puts (buffer);
    return 0;
}