#include <stdio.h>
#include <string.h>
#include <unistd.h>

void loop(char* buf) {
    int len = strlen(buf);
    char c;
    for (int i = 0; i < len; i++) {
        c = buf[i] - '0';
        printf("%d\n", c);
        sleep(1);
        if(i == 4) i = -1;
    }
    putchar('\n');
}

int main()
{
    char BUF[10]; 
    printf("请输入五个数字：");
    scanf("%s", BUF);
    loop(BUF);
    return 0;
}