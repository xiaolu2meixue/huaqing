#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, const char *argv[])
{
    int num1 = 100;

    printf("num1 = %d\n", num1);         //输出十进制数据 100
    printf("num1 = %#o\n", num1);            //输出八进制数据，#说明要输出先导符
    printf("num1 = %#x\n", num1);            //输出十六进制数


    int num2 = 0100;         //定义变量存储八进制数据
    printf("num2 = %d\n", num2);         //输出十进制数据 100
    printf("num2 = %#o\n", num2);            //输出八进制数据，#说明要输出先导符
    printf("num2 = %#x\n", num2);            //输出十六进制数

    int num3 = 0x100;         //定义变量存储八进制数据
    printf("num3 = %d\n", num3);         //输出十进制数据 100
    printf("num3 = %#o\n", num3);            //输出八进制数据，#说明要输出先导符
    printf("num3 = %#x\n", num3);            //输出十六进制数
    return 0;
}
