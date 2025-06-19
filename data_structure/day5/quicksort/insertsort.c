#include <myhead.h>

void insertsort(int* array)
{
    // 直接插入排序（原地排序）
    for (int i = 1; i < 5; i++) {  // 从第二个元素开始
        int key = array[i];        // 保存当前要插入的元素
        int j = i - 1;
        for ( ; j >= 0 && array[j] > key; j--) array[j + 1] = array[j];  // 将比key大的元素向后移动
        array[j + 1] = key;  // 插入到正确位置
    }
}
int main()
{
    int* arr = (int*)malloc(sizeof(int) * 5);
    printf("输入5个数字(空格隔开):");
    for (int i = 0; i < 5; i++) scanf("%d", &arr[i]);
    printf("原数组为：");
    for (int i = 0; i < 5; i++) printf(" %d", arr[i]);
    printf("\n");
    insertsort(arr);
    printf("排序后为：");
    for (int i = 0; i < 5; i++) printf(" %d", arr[i]);
    printf("\n");
    free(arr);
    arr = 0;
    return 0;
}
