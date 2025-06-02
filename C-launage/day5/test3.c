#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int i, j, z;
	for ( i = 1; i <= 4; i++)
	{
		for( z = i; z <= 3; z++)
			{
				printf(" ");
			}
		for ( j = 1; j <= i; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
