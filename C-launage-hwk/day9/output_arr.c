#include <myhead.h>
#define MAX_NUM 10

typedef struct employee {
    int id;
    char name[15];
    int sex;
}employee;

int input_arr(employee* arr)
{
    int max_count;
    for (size_t i = 0; i < MAX_NUM; i++) {
        printf("请输入数组元素:（输入-1结束输入）");
        scanf("%d", &arr[i].id);

        if(arr[i].id == -1) {
            max_count = i + 1;
            return max_count;
        }
    }
    
}
void output_arr()
{
    employee* employee_arr = (employee*)malloc(sizeof(employee) * MAX_NUM);
    int len = input_arr(employee_arr);
    //循环打印数组
    for(int i = 0; i < len -1; i++) printf("employee_arr[%d].id = %d\n", i, employee_arr[i].id);
    free (employee_arr);
    employee_arr = NULL;
}
int main(int argc, const char *argv[])
{
    output_arr();
	return 0;
}