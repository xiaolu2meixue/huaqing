#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int i, j;
	for ( i = 1; i <= 4; i++)
	{
		for ( j = 4; j >= 5 - i; j--)
		{
			printf("*");
		}
		printf("\n");
	}

	return 0;
}
