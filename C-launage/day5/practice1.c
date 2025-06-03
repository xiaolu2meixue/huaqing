#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int huiwen_num(int num)
{
	if(num < 0) return 0;
	char str1[20];
	sprintf(str1,"%d",num);
	int len = strlen(str1);
	char* left = str1;
	char* right = str1 + len - 1;
	for (; left < right; left++, right--){
		if (*left != *right) return 0;
	}
	return 1;
}
int main(int argc, const char *argv[])
{
	int NUM = 0;
	printf("请输入数字：");
	scanf("%d",&NUM);
	int x = huiwen_num(NUM);
	if (x) printf("%d 是回文数\n", NUM);
	else printf("%d 不是回文数\n", NUM);
	return 0;
}