#include <myhead.h>

// int* mymalloc(int value)
// {
//     int* arr = NULL;
//     arr = (int*)malloc(value * sizeof(int));
//     //init 
//     return arr;
// }

int main(int argc, const char* argv[])
{
    int* arr = (int*)malloc(5 * sizeof(int));
    if(arr == NULL) {
        printf("1111111\n");
        return -1;
    }
    for(int i = 0; i < 5; i++) {
        arr[i] = i;
        int* p = arr;
        printf("arr[%d] = %d\t", i, *p++); //*arr++  ++*arr
    }
    free(arr);
    arr = NULL;

    return 0;
}

//arr = array