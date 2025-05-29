#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define USERNAME "xuanzhonglu"
#define PASSWD 1234
int is_passwd(int password, int correct)
{
	if(password == correct) return 0;
	return 1;
}
int is_username(char* buf, const char* username)
{
	if(!strcmp(buf, username)) return 0;
	return 1;
}
int is_user(int password, char* buf, int correct, const char*username)
{
	int ret_pwd = is_passwd(password, correct);
	int ret_user = is_username(buf,username);
	if((!ret_user && !ret_pwd)) return 1;
	else if (ret_user ) return 2;
	else return 0;
}
int main(int argc, const char *argv[])
{
	char buffer[15] = {0};
	int passwd =0;
	int count = 0;
	do
	{
		printf("请输入用户名：");
		scanf("%s", buffer);
		printf("请输入密码：");
		scanf("%d", &passwd);
		int ret = is_user(passwd, buffer, PASSWD, USERNAME);
		if (ret == 1){
			printf("登陆成功，谢谢！");
			break;
		}
		else if(ret == 2) printf("没有该用户，请重新输入!\n");
		else {
			printf("密码错误，请重新输入\n");
			count++;
		}
	} while (count<3);
	if (count == 3) printf("错误次数过多，系统被锁定！");
	else return 0;
}
