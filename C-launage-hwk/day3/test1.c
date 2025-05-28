#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define USERNAME "xuanzhonglu"
#define PASSWD   1234

//判断用户名密码函数
int is_passwd(int password, int correct)
{
    if(password == correct) return 0;
    return 1;
}

int is_username(char* buf, const char* username)  //0表示判断成功
{
    if(!strcmp(buf, username)) return 0;
    return 1;
}

int is_user(int password, char* buf, int correct, const char* username)
{
    int ret_pwd = is_passwd(password, correct);
    int ret_user = is_username(buf, username);
    if((!ret_user) && (!ret_pwd)) {
        printf("登录成功！谢谢\n");
        return 0;
    }
    else if(ret_user) printf("没有该用户！\n");
    else printf("密码错误！\n");
    return 1;//失败
}

int main()
{
    char buffer[15] = {0};
    int passwd = 0;
    int ret;

    while(1) {
        printf("请输入用户名:");
        scanf("%s", buffer);
        //printf("用户名:%s", buffer);
        
        printf("\n请输入密码:");
        scanf("%d", &passwd);
        ret = is_user(passwd, buffer, PASSWD, USERNAME);
        if(!ret) break;

    }
    
    return 0;
}