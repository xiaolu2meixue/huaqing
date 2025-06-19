#include "stack.h"
//1、创建顺序栈
stack* create_stack()
{
    stack* S = (stack*)malloc(sizeof(stack));
    if (S == NULL) {
        printf("堆内存分配失败");
        return NULL;
    }
    S->top = -1; // 初始化栈顶指针
    return S;
}
//2、判空
int empty_stack(stack* S)
{
    return (S->top == -1);
}
//3、判满
int full_stack(stack* S)
{
    return (S->top == MAX - 1);
}
//4、入栈
void push_stack(stack* S, int value)
{
    if (full_stack(S)) {
        printf("栈已满，无法入栈\n");
        return;
    }
    S->data[++S->top] = value;
}
//5、出栈
int pop_stack(stack* S)
{
    if (empty_stack(S)) {
        printf("栈为空，无法出栈\n");
        return -1;  //false
    }
    return S->data[S->top--];
}
//6、输出栈中元素
void show_stack(stack* S)
{
    if (empty_stack(S)) {
        printf("栈为空\n");
        return;
    }
    
    printf("栈元素（栈底->栈顶）: ");
    for (int i = S->top; i <= S->top; i++) {
        printf("%d ", S->data[i]);
    }
    printf("\n");
}
//7、销毁栈
void destory(stack* S)
{
    if (S != NULL) {
        free(S);  
        S = NULL; 
    }
}