#include <stdio.h>
#include <math.h>  // 添加math.h以使用sfab函数

#define MIN 1e-6
int is_greater(float num)
{
    return num > MIN;
}
int is_less(float num)
{
    return num < -MIN;
}
int is_equal(float num)
{
    return fabs(num) < MIN;
}
void compare_and_print(float num) {
    if (is_greater(num))
	{
        printf("%f > 0\n", num);
    }
	else if (is_less(num))
	{
        printf("%f < 0\n", num);
    }
	else if (is_equal(num))
	{
        printf("%f ≈ 0 (在误差范围内)\n", num);
    }
	else
	{
        printf("未知状态: %f\n", num);
    }
}

int main() 
{
    float input_num;
    
    printf("请输入数字：");
    if (scanf("%f", &input_num) != 1)
	{
        printf("输入无效！\n");
        return 1;
    }
    printf("\n比较结果 (MIN = %g):\n", MIN);
    
    compare_and_print(input_num);  
    return 0;
}