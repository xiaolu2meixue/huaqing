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
void select_sort(int* arr1, int len1)
{
    if (len1 <= 1) return;  // 无需排序
    
    for (int *end = arr1 + len1 - 1; end > arr1; end--) {
        int *max = arr1;  // 初始化最大值指针
        
        // 在[arr, end]范围内查找最大值
        for (int *p = arr1 + 1; p <= end; p++) {
            if (*p > *max) {
                max = p;
            }
        }
        
        // 将最大值交换到末尾
        if (max != end) {
            int temp = *end;
            *end = *max;
            *max = temp;
        }
    }
}
int main(int argc, const char *argv[])
{
	int array[100];
	int len = Arr(array); //传递数组与数组长度
    select_sort(array, len); //调用选择排序函数

    //循环打印数组
    for (int i = 0; i < len; i++)
    {
        printf(" %d",array[i]);
    }
    printf("\n");
	return 0;
}