#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, const char *argv[])
{
	int i;
	for(i=1; i <= 100; i++){
		if (i%7 == 0 || i%10 ==7 ||i/10 == 7) continue;
		printf("%d\n",i);
	}
	return 0;
}
