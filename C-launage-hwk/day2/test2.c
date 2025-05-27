#include <stdio.h>
#include <string.h>
#define r (x)
#define PAI 3.1415926
#define S PAI*r*r
int main(int argc, const char *argv[])
{
	int x;
	printf("please input the radius of the cirle:");
	scanf("%d",&x);
	printf("%s %f\n","the area of circle is",S);
	return 0;
}
