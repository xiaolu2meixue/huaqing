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
int is_Arr()
{
	int ARR[100];
	int size = Arr(ARR);
	int num;
	printf("请输入一个数字：");
	scanf("%d", &num);
	for (int j = 0; j < size; j++)
	{
		if (ARR[j] == num) return 0;
	}
	return 1;
}
int main(int argc, const char *argv[])
{
	if (!is_Arr()) printf("该数字属于该数组\n");
	else printf("该数字不属于该数组\n");
	return 0;
}
