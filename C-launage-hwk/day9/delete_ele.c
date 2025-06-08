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
int is_post()
{
    int post = -1;
    printf("请输入需要删除第几个元素：");
    scanf("%d", &post);
    return post == -1? 0: post; //返回值0为false
}
//删除数组元素
int delete_ele(employee* arr,int rel_len, int post)
{
    employee* index = &arr[post -1];
    employee* temp = index;
    for ( ;&arr[rel_len - 1] > index; *temp = *++index, temp++);
    memset(&arr[rel_len - 1], 0, sizeof(employee));
    //end->id = 0; 
}

int main(int argc, const char *argv[])
{
    employee* employee_arr = (employee*)malloc(sizeof(employee) * MAX_NUM);
    int len = input_arr(employee_arr);
    delete_ele(employee_arr, len, is_post());

    for(int i = 0; i < len -2; i++) printf("employee_arr[%d].id = %d\n", i, employee_arr[i].id);

    free (employee_arr);
    employee_arr = NULL;
	return 0;
}
