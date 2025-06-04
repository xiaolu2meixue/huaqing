#include <myhead.h>
int main(int argc, const char *argv[])
{
	int arr[2][3] = {23, 42, 87, 11, 100, 17};
	int max = 0, scd = 0;
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			if (arr[i][j] >= max) max = arr[i][j];
		}
		
	}
    for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			if (arr[i][j] < max && arr[i][j] >= scd) scd = arr[i][j];
		}
		
	}
    
	printf("第二大值为：%d\n", scd);
	return 0;
}