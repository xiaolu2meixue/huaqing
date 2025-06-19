#include "links.h"
int main(int argc, const char* argv)
{
    node* S = NULL;
    
    printf("创建空栈...\n");
    print_stack(&S);  // 打印空栈
    
    // 入栈操作
    printf("\n入栈1...\n");
    push_stack(&S, 1);
    print_stack(&S);
    
    printf("\n入栈2...\n");
    push_stack(&S, 2);
    print_stack(&S);
    
    printf("\n入栈3...\n");
    push_stack(&S, 3);
    print_stack(&S);
    
    printf("\n入栈4...\n");
    push_stack(&S, 4);
    print_stack(&S);
    return 0;
}