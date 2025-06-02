#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int i, j;
	for ( i = 1; i <= 9; i++)
	{
		for ( j = 1; j <= i; j++)
		{
			printf("%d * %d = %d ",i,j,i*j);
		}
		printf("\n");
	}
	return 0;
}
