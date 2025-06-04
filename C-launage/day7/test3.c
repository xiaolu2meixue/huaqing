#include <myhead.h>
int Str(char* str)
{
	printf("请输入字符串1：");
	gets(str);
	int len = strlen(str);
    return len;
}
int atoi_1()
{
    char buf[128] = "";
    int LEN = Str(buf);
    int start = 0, sum = 0;
    for (; start <= LEN && buf[start] == ' '; start++); //跳过空格
    if (start >= LEN) return 0;
    //第一个字符不为数字或正负号，输出0
    if ('0' > buf[start] || buf[start] > '9') {
            if (buf[start] != '-' && buf[start] != '+') return 0;
            if (start + 1 >= LEN || !isdigit(buf[start + 1])) return 0;
        }
    int sign = 1;
    if (buf[start] == '-') {
        sign = -1;
        start++;
    } else if (buf[start] == '+') {
        start++;
    }
    for (int i = start; i < LEN; i++) {
        if ('0' > buf[i] || buf[i] > '9') break;
        sum = sum * 10 + (buf[i] - '0');
    }

    return sign * sum;
}
int main(int argc, const char *argv[])
{
    int SUM = atoi_1();
    printf("%d\n",SUM);
    return 0;
}
