#include <myhead.h>
int main(int argc, const char *argv[])
{
	int arr[2][3] = {1, 2, 3, 4, 5, 6};
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 1; j++)
		{
			printf("%d ",arr[j][i]);
		}
		putchar(10);
	}
	
	return 0;
}
