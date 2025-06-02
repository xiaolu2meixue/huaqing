#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void Target(int target)
{
    int ARR[100];
    int NUM = Arr(ARR);
    int found = 0;
    for (int i = 0; i < NUM; i++) {
        for (int j = i + 1; j < NUM; j++) {
            if (ARR[i] + ARR[j] == target) {
                printf("解：%d %d\n", i, j);
                found = 1;
                continue;
            }
        }
    }
    
    if (!found) {
        printf("无解\n");
    }
}
int main(int argc, const char *argv[])
{
    int TARGET;
    printf("请输入目标数字：");
    scanf("%d", &TARGET);
    Target(TARGET);
    return 0;
}