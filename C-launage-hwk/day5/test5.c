#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Arr(int* arr)
{
	int num;
	for (int count = 0; ;count++)
	{
		printf("请输入：（输入-1结束输入）");
		scanf("%d", &num);
		if (num == -1) return count;
		arr[count] = num;
	}
    return 0;
}
int Max()
{
    int ARR[100];
    int size = Arr(ARR);
    int max = ARR[0];
    for (int j = 0; j < size; j++)
    {
        if (ARR[j] > max) max = ARR[j];
    }
    return max;
}
int main(int argc, const char *argv[])
{
    int MAX = Max();
	printf("最大值为：%d\n", MAX);
	return 0;
}
