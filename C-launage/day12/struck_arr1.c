#include <myhead.h>
typedef struct employee {
    int id;
    char* name;
    int sex;
    int* data;
} employee;
// 输入函数：返回分配好的数组指针，并通过count参数返回数组大小
employee* init_arr(int *count)
{
    printf("请输入需要输入的数组数：");
    scanf("%d", count);
    employee *arr = (employee*)malloc(*count * sizeof(employee));
    for (int i = 0; i < *count; i++) {
        arr[i].data = (int*)malloc(sizeof(int) * 5);
        
        printf("请输入数组%d的元素(输入五个数，空格隔开)：", i + 1);
        for (int j = 0; j < 5; j++) scanf("%d", &arr[i].data[j]);
    }
    return arr;
}
// 打印函数：打印所有数组内容
void print_arr(employee *arr, int count)
{
    for (int i = 0; i < count; i++) {
        printf("第%d个数组为：", i + 1);
        for (int j = 0; j < 5; j++) printf("%-4d ", arr[i].data[j]);
        printf("\n");
    }
}
int main(int argc, const char *argv[])
{
    int count = 0;
    // 调用输入函数
    employee *arr = init_arr(&count);
    // 调用打印函数
    print_arr(arr, count);
    // 释放内存
    for (int i = 0; i < count; i++) free(arr[i].data);
    free(arr);
    arr = NULL;
    return 0;
}