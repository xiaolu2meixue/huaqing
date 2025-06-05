#include <myhead.h>
int my_sum(int Row, int Col, int (*arr)[Col])
{
	int i, j;
	int Sum;
	for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            //行求和
            if (i == 0) Sum += arr[i][j];
            else sum_l2 += arr[i][j];
            //列求和
            if (j == 0) sum_c1 += arr[i][j];
            else if (j == 1) sum_c2 += arr[i][j];
            else sum_c3 += arr[i][j];
        }
	}
}
int main(int argc, const char *argv[])
{
	int row, col;
	printf("请输入行数：");
	scanf("%d", &row);
	printf("请输入列数：");
	scanf(" %d", &col);
	int arr[row][col];
	memset(arr, 0, sizeof(arr));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			scanf("%d", &arr[i][j]);
		}
		
	}
	
	return 0;
}
