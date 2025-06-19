#include "links.h"

node* create_node(int value)
{
	node* new = (node*)malloc(sizeof(node));
	if(new == NULL) return NULL;
	new->next = NULL;
	new->data = value;
	return new;
}
//2、判空
int empty_stack(node** S)
{
    return *S == NULL;
}
//3、入栈
//入栈操作需要修改主函数中栈顶指针的指向
void push_stack(node** S, int value)
{
    //S是二级指针
    if(S == NULL) return;
    node* new  = create_node(value);
    new->next = *S;  // 新节点指向原栈顶
    *S = new;        // 更新栈顶指针指向新节点
}
void print_stack(node** S)
{
    if (empty_stack(S)) {
        printf("栈为空\n");
        return;
    }
    
    printf("栈顶 -> ");
    node* p = *S;  // 创建临时指针用于遍历
    
    for ( ; p != NULL; p = p->next) {
        printf("%d", p->data);
        if (p->next != NULL) {
            printf(" -> ");  // 添加箭头连接元素（最后一个元素不加）
        }
    }
    printf("\n");  // 输出换行符
}