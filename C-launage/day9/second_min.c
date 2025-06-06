#include <myhead.h>
//输入数组
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
//找到第二大值
int scd_arr(int* arr1, int len1)
{
	//先找到最大值
	int max = *arr1, scd = 0;
	int* left = arr1;
	int* right = arr1 + len1 - 1;
	for (; left <= right; left++) {
		if (max <= *left) max = *left;
	}
	//从第一个开始判断，找到第一个不是最大值的数
	left = arr1;
	for (; left <= right; left++) {
		if (*left != max) {
			scd = *left;
			break;
		}
	}
	//找到第二大值
	for (; left <= right; left++) {
		if (scd <= *left && *left < max) scd = *left;
	}
	return scd;
}
int main(int argc, const char *argv[])
{
	int array[100];
	int len = Arr(array);
	//printf("%d\n",len);
	int scd_num = scd_arr(array, len);
	printf("%d\n",scd_num);
	return 0;
}
