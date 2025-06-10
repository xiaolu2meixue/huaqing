#include "myhead.h"

typedef struct {
    int *data;  // 存储该行数据的数组
    int length; // 该行的长度（元素个数）
} yanghui;

int my_yanghui(int total_rows)
{
    yanghui *triangle = (yanghui *)malloc(total_rows * sizeof(yanghui));
    for (int i = 0; i < total_rows; i++) {
        int currentLength = i + 1;
        triangle[i].length = currentLength;
        triangle[i].data = (int *)malloc(currentLength * sizeof(int));

        // 填充已知行数据
        triangle[i].data[0] = 1; // 每行第一个元素为1
        triangle[i].data[i] = 1; // 每行最后一个元素为1
        
        // 计算中间元素（从第2行开始）
        if (i > 1) {
            for (int j = 1; j < i; j++) {
                // 当前值 = 上一行左上方值 + 上一行正上方值
                triangle[i].data[j] = triangle[i-1].data[j-1] + triangle[i-1].data[j];
            }
        }
    }
    for (int i = 0; i < total_rows; i++) {
        // 打印前导空格实现居中对齐
        for (int q = 0; q < total_rows - i - 1; q++) {
            printf("   ");
        }
        
        // 打印当前行所有数字
        for (int j = 0; j < triangle[i].length; j++) {
            printf("%-6d", triangle[i].data[j]);
        }
        printf("\n");
    }
    //释放内存
    for (int i = 0; i < total_rows; i++) {
        free(triangle[i].data);
    }
    free(triangle);    
}
