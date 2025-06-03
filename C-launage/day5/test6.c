#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int i = 1, sum = 0;
	a:
	sum += i;
	i++;
	if (i == 6) goto b;
	goto a;
	b:	
	printf("sum=%d\n", sum);
	return 0;
}
