#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void ABCD(int grades)
{
	if (grades >=90 && grades <=100) printf("A\n");
	else if (grades >=80 && grades <=89) printf("B\n");
	else if (grades >=70 && grades <=79) printf("C\n");
	else if (grades >=0 && grades <=69) printf("B\n");
	else printf("错误，请输入0~100数字\n");
}
int main(int argc, const char *argv[])
{
	int GRADES;
	printf ("请输入成绩：");
	scanf ("%d",&GRADES);
	ABCD (GRADES);
	return 0;
}
