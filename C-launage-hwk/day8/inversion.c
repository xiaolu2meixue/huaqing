#include <myhead.h>
void invert(char* buf1, int start, int end) {
    if (start >= end) return;
    char temp = buf1[start];
    buf1[start] = buf1[end];
    buf1[end] = temp;
    invert(buf1, start + 1, end - 1);
}
int main(int argc, const char *argv[])
{
    char buf[128] = { 0 };
	printf("请输入字符串：");
    fgets(buf, 128, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    int len = strlen(buf);
    invert(buf, 0 ,len - 1);
    printf("倒置字符串为：");
    fputs(buf,stdout);
    printf("\n");
	return 0;
}
