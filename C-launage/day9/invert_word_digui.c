#include <myhead.h>
char* invert(char* str, char* left1, char* right1)
{
    if(left1 >= right1){
       return str;
    }
    int temp = *left1;
    *left1 = *right1;
    *right1 = temp; 
    left1++;
    right1--;
    invert(str, left1, right1);
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
    char* left = buf;
    char* right = buf + len - 1;
    //初始化buffer用于接收invert函数的返回值
    char* buffer = NULL;
    buffer = invert(buf, left, right);
    //输出字符串
    fputs(buffer, stdout);
    printf("\n");
	return 0;
}