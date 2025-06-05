#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    //int i;
    char str[5][10] = { 0 };
    char temp[10] = { 0 };
    for (int i = 0; i < 5; i++) {
        printf("请输入姓名：");
        fgets(str[i], 10, stdin);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (strcmp(str[j], str[j + 1]) > 0) {
                
                strcpy(temp, str[j]);
                strcpy(str[j], str[j + 1]); 
                strcpy(str[j + 1], temp);
            }
            memset(temp, 0, sizeof(temp));
            //bzero(temp,sizeofz(temp))
        }

    }

    for (int i = 0; i < 5; i++) fputs(str[i], stdout);
    return 0;
}