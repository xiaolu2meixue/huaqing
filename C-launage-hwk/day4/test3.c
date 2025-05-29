#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void endless_loop() {
    while(1) {
        printf("我是奶龙...\n");
        for(long long i = 0; i < 999999999; i++);//控制打印速度
    }
}

int main(int argc, const char *argv[])
{
    printf("即将进入死循环，按下ctrl c 退出\n");
    endless_loop();
    printf("代码错误，不为死循环\n");
    return 0;
}