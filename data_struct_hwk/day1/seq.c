#include "seq.h"


seq* creat_seq()
{
    seq* S = (seq*)malloc(sizeof(seq));
    S->max_len = 5;
    S->arr = (int*)malloc(sizeof(int) * S->max_len);
    if (!S && !S->arr) {
        printf("fail\n");
        return NULL;
    }
    memset(S->arr, 0, sizeof(S->arr));
    return S;
}
//判空
int empty_seq(seq* S)
{
    //seq* S = creat_seq(); 
    if (S == NULL) {
        printf("入参为空\n");
        return MYNULL;
    }
    return S->len == 0? EMPTY: SUSSES;
}
//判满
int full_seq(seq* S)
{
    //seq* S = creat_seq();
    if (S == NULL) {
        printf("入参为空\n");
        return MYNULL;
    }
    return S->len == S->max_len? FULL: SUSSES;
}
//头插
void insert_head(int data, seq* S)
{
    //seq* S = creat_seq();
    if (full_seq(S) == FULL) {
        int* arr = (int*)realloc(S->arr, sizeof(int) * S->max_len *2);
        S->arr = arr;
        S->max_len *= 2;
    }

   if (S->len > 0) {
        for (int i = S->len - 1; i >= 0; i--) {
            S->arr[i + 1] = S->arr[i];
        }
    }

    S->arr[0] = data;
    S->len++;
    printf("%d \n", S->arr[0]);
    printf("已插入%d  len = %d\n", data, S->len);
}
void insert_end(int data, seq* S)
{
    //seq* S = creat_seq();
    if (full_seq(S) == FULL) {
        int* arr = (int*)realloc(S->arr, sizeof(int) * S->max_len *2);
        S->arr = arr;
        S->max_len *= 2;
    }


    S->arr[S->len] = data;
    S->len++;
    printf("%d \n", S->arr[0]);
    printf("已插入%d  len = %d\n", data, S->len);
}

void delete_end(seq* S)
{
    if(empty_seq(S) == EMPTY) {
        printf("数组为空\n");
        return;
    }

    S->arr[S->len] = 0;
    S->len--;
}

void delete_start(seq* S)
{
    if(empty_seq(S) == EMPTY) {
        printf("数组为空\n");
        return;
    }

   if (S->len > 0) {
        for (int i = 0; i < S->len; i++) {
            S->arr[i] = S->arr[i + 1];
        }
    }

    S->len--;
}
void insert_pos(seq* S)
{
    if(empty_seq(S) == EMPTY) {
        printf("数组为空\n");
        return;
    }
    if (full_seq(S) == FULL) {
        int* arr = (int*)realloc(S->arr, sizeof(int) * S->max_len *2);
        S->arr = arr;
        S->max_len *= 2;
    }
    int num, ele;
    printf("输入在第几个位置插入元素：");
    scanf("%d", &num);
    getchar();
    if (num > S->len + 1) printf("超出顺序表长度");
    printf("输入插入的元素：");
    scanf("%d", &ele);
    getchar();
    for(int i = S->len; i >= num; i--) S->arr[i] = S->arr[i - 1];
    S->arr[num - 1] = ele;
    S->len += 1;
}
void find_pos(seq* S)
{
    
}