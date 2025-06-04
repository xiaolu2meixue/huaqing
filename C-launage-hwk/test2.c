#include <myhead.h>
int main(int argc, const char *argv[])
{
	int arr[2][3] = {23, 42, 87, 11, 100, 17};
    int sum_l1 = 0, sum_l2 = 0, sum_c1 = 0, sum_c2 = 0, sum_c3 = 0;
    int i, j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            //行求和
            if (i == 0) sum_l1 += arr[i][j];
            else sum_l2 += arr[i][j];
            //列求和
            if (j == 0) sum_c1 += arr[i][j];
            else if (j == 1) sum_c2 += arr[i][j];
            else sum_c3 += arr[i][j];
        }
        
    }
    printf("第1行总值：%d\n第2行总值：%d\n第1列总值：%d\n第2列总值：%d\n第3列总值：%d\n",sum_l1, sum_l2, sum_c1, sum_c2, sum_c3);
}