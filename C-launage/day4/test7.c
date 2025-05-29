#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int place(int num )
{
	int count = 0
	while()
	{
		num=num/10;
		count++;
		if(num=0) break;
	}
	
	return count;
}
int main(int argc, const char *argv[])
{
	int NUM;
	int COUNT;
	scanf ("%d\n",&NUM);
	COUNT=place(NUM);
	printf("%d",COUNT);
	return 0;
}
