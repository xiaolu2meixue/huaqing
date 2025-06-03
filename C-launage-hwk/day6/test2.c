#include <myhead.h>
int Str(char* str)
{
	printf("请输入字符串：");
	gets(str);
	int len = strlen(str);
    return len;
}
int output_num(char* buf) 
{
    Str(buf);
    int sum = 0;
    int found_digit = 0;

    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] >= '0' && buf[i] <= '9') {
            sum = sum * 10 + (buf[i] - '0');
            found_digit = 1;
        }
    }
    return sum;
}
int main(int argc, const char *argv[])
{
    char BUFFER[100] = {};
    int result = output_num(BUFFER);
    printf("%d\n",result);
    return 0;
}