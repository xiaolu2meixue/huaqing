#include <myhead.h>
char* invert(char* str, int len1)
{
    char* left = str;
    char* right = str + len1 - 1;
    for (; left < right; left++, right--){
        int temp = *left;
        *left = *right;
        *right = temp; 
    }
    return str;
}
int main(int argc, const char *argv[])
{
    char buf[20];
    //输入字符串
    printf("请输入单词：");
    fgets(buf, 20, stdin);
    //去掉末尾\n
    buf[strlen(buf) - 1] = '\0';
    //计算字符串长度
    int len = strlen(buf);
    //初始化buffer用于接收invert函数的返回值
    char* buffer = NULL;
    buffer = invert(buf, len);
    //输出字符串
    fputs(buffer, stdout);
    printf("\n");
	return 0;
}