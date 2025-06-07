#include <myhead.h>
//输入数组
int Arr(int* arr)
{
	int num;
    //循环输入数组
	for (int count = 0; ;count++) {
		printf("请输入：（输入-1结束输入）");
		scanf("%d", &num);
		if (num == -1) return count; //输入-1结束输入
		arr[count] = num;
	}
    return 0;
}
void insert(int* arr1, int len1, int which1, int num1)
{
    int* insert1 = arr1 + which1 - 1;
    arr1[len1] = num1; //先把插入的数字插入到数组末尾
    int* end = arr1 + len1;
    //调换顺序，重组数组
    for ( ; insert1 < end; insert1++) {
        int temp = *insert1;
        *insert1 = *end;
        *end = temp;
    }  
}
int main(int argc, const char *argv[])
{
	int array[100];
	int len = Arr(array); //传递数组与数组长度
    int which;
    // 输入插入位置，并确保插入位置不大于数组长度
    for ( ; ; ) {
        printf("请输入在数组第几个元素插入：");
        scanf("%d", &which);
        if (which <= len + 1) {
            break;
        }
        else printf("输入错误，重新输入");
    }
    printf("请输入需要插入的元素："); //输入插入的元素
    int num;
    scanf("%d", &num);
    insert(array, len, which, num); //调用插入函数

    //循环打印数组
    for (int i = 0; i <= len; i++) {
        printf(" %d",array[i]);
    }
    printf("\n");
	return 0;
}