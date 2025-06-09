#include <myhead.h>
int main(int argc, const char *argv[])
{
	int arr1[] = {1, 2};
	int arr2[] = {3, 4, 6, 8};
	int arr3[] = {5, 6};
	int* p[] = {arr1, arr2, arr3};
	size_t sizes[3] = {sizeof(arr1) / sizeof(arr1[0]), sizeof(arr2) / sizeof(arr2[0]), sizeof(arr3) / sizeof(arr3[0])};
	for (size_t i = 0; i < sizeof(p)/sizeof(p[0]); i++) {
		int* q = p[i];
		for (size_t j = 0; j < sizes[i]; j++) {
			printf("%d \t", *q);
			q++;
		}
		printf("\n");
	}	
	return 0;
}