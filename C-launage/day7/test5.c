#include <myhead.h>
int main(int argc, const char *argv[])
{
	int arr[2][3] = {23, 42, 87, 11, 100, 17};
	int max = 0;
	int i, j;
	for (i = 0; i <= 1; i++)
	{
		for (j = 0; j <= 2; j++)
		{
			if (arr[i][j] >= max) max = arr[i][j];
		}
		
	}
	printf("最大值为：%d", max);
	return 0;
}
