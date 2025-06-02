#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	float arr[5] = {0.2, 0.7, 0.9, 0.8, 0.86};
	int i = 0;
	float sum;
	for (i=0; i < 5; ++i) {
		sum += arr[i];
	}
	printf("sum=%f",sum);
	return 0;
}
