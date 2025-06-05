#include <myhead.h>
void yanghui(int x ,int (*arr)[x])
{
	int i, j;
	for (i = 0; i < x; i++)
	{
        for (int p =  x; p >= i; p--)
        {
            printf("   ");
        }
		for (j = 0; j <= i; j++)
		{
			if(j == 0 || i == j) {
				arr[i][j] = 1;
				printf("%d    ",arr[i][j]);
			}
			else {
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
				printf("%d    ",arr[i][j]);
			}
		}
		putchar(10);
	}
	return;
}
int main(int argc, const char *argv[])
{
	int n;
	printf("请输入层数：");
	scanf("%d",&n);
	int Arr[n][n];
	yanghui(n ,Arr);
	return 0;
}
