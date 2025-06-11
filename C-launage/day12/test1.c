#include <myhead.h>
typedef struct employee {
    int id;
    char* name;
    int sex;
    int* data;
}employee;
void input_arr()
{
    int count;
    printf("请输入需要输入的数组数：");
    scanf("%d", &count);
	employee *arr = (employee*)malloc(count * sizeof(employee));
    for (int i = 0; i < count; i++) {
        arr[i].data = (int*)malloc(sizeof(int) * 5);
        printf("请输入数组%d的元素(输入五个数，空格隔开)：", i + 1);
        for (size_t j = 0; j < 5; j++) scanf("%d", &arr[i].data[j]);
    }
    for (int i = 0; i < count; i++) {
        printf("第%d个数组为：", i + 1);
        for (size_t j = 0; j < 5; j++) printf("%-4d ", arr[i].data[j]);
        printf("\n");
    }
	for (size_t i = 0; i < count; i++) free(arr[i].data);
    free(arr);
    arr = NULL;   
}
int main(int argc, const char *argv[])
{
    input_arr();
    return 0;
}
