#include <myhead.h>
int main(int argc, const char *argv[])
{
	int arr[10][10] = {0};
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j <= i; j++)
		{
			if(j == 0 || i == j) {
				arr[i][j] = 1;
				printf("%d ",arr[i][j]);
			}
			else {
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
				printf("%d ",arr[i][j]);
			}
		}
		putchar(10);
	}
	return 0;
}
