#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, const char *argv[])
{
    int num = 520;


    printf("%d\n", num);        //无任何格式
    printf("%5d\n", num);        //至少给定5个空间输出数据，用不完的部分用空格补齐
    printf("%-5d\n", num);        //至少给定5个空间输出数据，用不完的部分用空格补齐
    printf("%05d\n", num);        //至少给定5个空间输出数据，用不完的部分用空格补齐
    

    return 0;
}
