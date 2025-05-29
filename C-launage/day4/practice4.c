#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int cir()
{
	int input;
	int output = 0;
	do{
		printf("请输入：");
		scanf("%d", &input);
		output += input;
		printf("%d\n", output);
	}while(input != 0);
	return 0;
}
int main(int argc, const char *argv[])
{
	cir();
	return 0;
}
