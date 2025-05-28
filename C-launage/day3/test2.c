#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int a=130;
	char b=(int)a;
	float c=(int)a;
	printf("%c\n",b);
	printf("%f\n",c);
	return 0;
}
