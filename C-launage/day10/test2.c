#include <myhead.h>
void arr(int (*arr)[4])
{
	int *p = *arr;
	for (int i = 0; i < 8; i++) {
		scanf("%d", p++);
	}
}
int main(int argc, const char *argv[])
{
	int (*array)[4] = (int(*)[4])malloc(sizeof(int[4]) * 2);
	arr(array);
	int* p = *array;
	for (int i = 0; i < 2; i++) {
		for (int i = 0; i < 4; i++) {
			printf("%d ", *p++);
		}
		printf("\n");
	}
	free(array);
	array = NULL;
	return 0;
}
