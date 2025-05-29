#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int ABCD(int grade)
{
	if (grade >= 90 && grade <= 100) return 9;
	else if (grade >= 70 && grade <= 89) return 8;
	else if (grade >= 60 && grade <= 79) return 7;
	else if (grade >= 0 && grade <= 59) return 6;
	else return 1;
}
int is_ABCD(int grade)
{
	int A = ABCD(grade);
	switch (A)
	{
	case 9:printf("A\n");break;
	case 8:printf("B\n");break;
	case 7:printf("C\n");break;
	case 6:printf("D\n");break;
	default:printf("输入错误\n");
	}
}
int main(int argc, const char *argv[])
{
	int GRADE;
	printf("请输入成绩：");
	scanf("%d",&GRADE);
	ABCD(GRADE);
	is_ABCD(GRADE);
	return 0;
}
