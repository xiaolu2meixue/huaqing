#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define a 897661761
void jiemian(int num,int A)
{
	int b,c;
	if (num==1) printf ("账户余额：$%d\n",A);
	else if (num==2)
	{
		printf("请输入存款金额：\n");
		scanf("%d",&b);
		if (b>=0) printf("存款成功，余额为:$%d\n",A+b);
		else ("输入错误");
	}
	else if (num==3)
	{
		printf("请输入取款金额:\n");
		scanf ("%d",&c);
		if (c>=0 && c<a) printf("取款成功，余额为:$%d\n",A-c);
		else if (c>=0 && c>A) printf("取款失败，余额不足");
		else printf("错误，非法操作");
	}
	else printf("输入错误，请输入数字1、2、3！\n");
}
int main(int argc, const char *argv[])
{
	int NUM;
	int M=a;
	printf ("按1查询账户余额\n按2存款\n按3取款\n");
	scanf("%d",&NUM);
	jiemian(NUM,M);
	return 0;
}
