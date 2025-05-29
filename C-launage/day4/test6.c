#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int SUM()
{
	int a = 1;
    int sum = 0;
    while(a <= 5)
    {
		printf("%d\n", a);
        sum += a; 
		++a;
	}
	printf("%d\n", sum);
	return 0;
}
int main(int argc, const char *argv[])
{
	SUM();
	return 0;
}
