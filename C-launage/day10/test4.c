#include <myhead.h>
void arr(int (*arr)[4])
{
	int *p = *arr;
	for (int i = 0; i < 8; i++) {
		scanf("%d", p++);
	}
}
int is_max(int (*myarr)[4])
{
    int *p = *myarr;
    int max = *p;
    for (int i = 0; i < 8; i++, p++) if (max <= *p) max = *p;
    return max;
}
int main(int argc, const char *argv[])
{
    int (*array)[4] = (int(*)[4])malloc(sizeof(int[4]) * 2);
    arr(array);
    int* p = *array;
    printf("原二维数组为：\n");
    for (int i = 0; i < 2; i++) {
		for (int i = 0; i < 4; i++) {
			printf("%-6d ", *p++);
		}
		printf("\n");
	}
    int max_num = is_max(array);
	printf("数组最大值为：%d\n", max_num);
    free(array);
    array = NULL;
    return 0;
}