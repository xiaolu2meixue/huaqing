#include "common.h"

user* regist()
{
    user* user1 = (user*)malloc(sizeof(user));
    printf("********  注册账号  ********\n");
    printf("请输入用户名：");
    fgets(user1->username, 15, stdin);
    user1->username[strcspn(user1->username, "\n")] = '\0';
    printf("请输入密码：");
    fgets(user1->passwd, 15, stdin);
    user1->passwd[strlen(user1->passwd) - 1] = '\0';
    return user1;
}

int is_user()
{
    user* user1 = regist();
    char username1[15], passwd1[15];
    int i;
    printf("*****  通讯录管理系统  *****\n");
    for ( ; ; ) {
        printf("请输入账号：");
        fgets(username1, 15, stdin);
        username1[strcspn(username1, "\n")] = '\0';
        if (strcmp(username1, user1->username)) printf("账号错误，请重新输入");
        else break;
    }
    for (i = 0; i < 3; i++) {
        printf("请输入密码：");
        fgets(passwd1, 15, stdin);
        passwd1[strlen(passwd1) - 1] = '\0';
        if (strcmp(passwd1, user1->passwd)) printf("密码错误，请重新输入");
        else {
            printf("登陆成功！\n");
            break;
        }
    }
    if (i == 3) {
        printf("\n错误次数过多，已被限制登陆！\n");
        free(user1);
        exit(0);
    }
    else {
        free(user1);
        return 0;
    }
}