#include <myhead.h>
int* fun()
{
	int a = 100;
	int b = 200;
	int* arr = (int*)malloc(sizeof(int*));
	arr[0] = a;
	arr[1] = b;
	return arr;
}
int main(int argc, const char *argv[])
{
	int* array = fun();
	printf("%d %d", *array, *(array + 1));
	free(array);
	array = NULL;
	return 0;
}
