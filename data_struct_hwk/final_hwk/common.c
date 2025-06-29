#include "common.h"

//创建头节点
node* creat_link()
{
    node* H = (node*)malloc(sizeof(node));
    if (H == NULL) {
        printf("申请内存失败\n");
        return NULL;
    }
    H->next = NULL;
    H->len = 0;
    return H;
}

//新建联系人节点
node* creat_node(person value)
{
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        printf("申请内存失败\n");
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

//判空
int empty_link(node* H)
{
    if (H == NULL) return -2;
    return H->next == NULL? 1: 0;
}

//尾插，即添加联系人
void insert_tail(node* H, person value)
{
    if (!H) return;
    node* p = H;
    for(; p->next; p = p->next);
    node* new = creat_node(value);
    p->next = new;
    H->len++;
}

void free_list(node* H)
{
    if (!H) return;
    
    node* cur = H->next;
    while (cur) {
        node* temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(H);
}