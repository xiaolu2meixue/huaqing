#include <myhead.h>
//数组的输入
int input_array(int* arr)
{
	int len;
	printf("请输入数组长度：");
	scanf("%d",&len);
    for(int i = 0; i < len; i++) {
		printf("请输入整数:");
        scanf(" %d", &arr[i]);
    }
	return len;
}
//冒泡排序
int sort(int* arr1)
{
	int Len = input_array(arr1);
	for (int i = 0; i < Len; i++) {
        for (int j = 0; j < Len - i - 1; j++) {
            if (arr1[j] >= arr1[j + 1]) {
				int temp = arr1[j];
				arr1[j] = arr1[j + 1];
				arr1[j + 1] = temp;
			}
		}
	}
	return Len;
}
//数组的打印
void myprint()
{
	int arr2[10] = { 0 };
	int len1 = sort(arr2);
	for(int i = 0; i < len1; i++) {
		printf(" %d\n", arr2[i]);
    }
}

int main(int argc, const char *argv[])
{
	myprint();
	return 0;
}
