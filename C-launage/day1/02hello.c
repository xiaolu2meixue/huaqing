#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, const char *argv[])
{

    printf("hello \t world\n");
    //功能：向终端中输出字符串数据
    //里面是英文状态下的双引号
    //双引号内的内容可以是任意的，就是展现到终端上的内容
    //'/n'表示的是换行
    //';'表示这是一条完整的语句，语句的标志就是分号
    //'\t'是一个制表符，一个TAB键的内容

    //以下是多行注释
    /*
    这里是多行注释
    可以在同一行
    也可以在不同行
    */

#if 0
里面的都是注释内容
可以在同一行
也可以在不同行
#endif
    return 0;
}