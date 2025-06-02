#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void paixu(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int *buf = arr; buf < arr + size - 1 - i; buf++) {
            if (*buf > *(buf + 1)) {
                int temp = *buf;
                *buf = *(buf + 1);
                *(buf + 1) = temp;
            }
        }
    }
}

int main(int argc, const char *argv[])
 {

	int n;
	scanf
    int arr[n];
	int i;
	for ( i = 0; i < 5; i++)
	{
		printf("请输入数字：");
		scanf("%d",&arr[i]);
	}
	
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("原始数组: ");
    for (int *buf = arr; buf < arr + size; buf++) {
        printf("%d ", *buf);
    }
    printf("\n");
    
    paixu(arr, size);
    
    printf("升序排序: ");
    for (int *buf = arr; buf < arr + size; buf++) {
        printf("%d ", *buf);
    }
    printf("\n");
    
    return 0;
}