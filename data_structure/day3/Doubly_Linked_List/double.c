#include "double.h"

//申请双链表（头节点）
node* creat_double()
{
    node* H = (node*)malloc(sizeof(node));
    if (H == NULL) {
        printf("申请内存失败\n");
        return NULL;
    }
    H->prev = NULL;
    H->next = NULL;
    H->len = 0;
    return H;
}
//申请数据节点
node* creat_node(int value)
{
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        printf("申请内存失败\n");
        return NULL;
    }
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}
//判空
int empty_double(node* H)
{
    if (H == NULL) return -2;
    return H->next == NULL? 1: 0;
}
//头插
void insert_head(node* H, int value)
{
    node* new_node = creat_node(value);
    if (H->next == NULL) {  // 空链表
        H->next = new_node;
        new_node->prev = H;
    }
    else {
        new_node->next = H->next;
        new_node->prev = H;
        H->next->prev = new_node;
        H->next = new_node;
    }
    H->len++;
    // node* new_node = creat_node(value);
    // //新结点的后继保存原来头结点的后继
    // new_node->next = H->next;
    // //新结点的前驱指向头结点
    // new_node->prev = H;
    // //头结点后继节点的前驱指向新结点
    // if (H->next != NULL) {
    //     H->next->prev = new_node;
    // }
    // //头结点的后继指向新结点
    // H->next = new_node;
    // H->len++;
}
//尾插
void insert_tail(node* H, int value)
{
    node* new_node = creat_node(value);
    if (H->next == NULL) {  
        H->next = new_node;
        new_node->prev = H;
    }
    else {
        node* p = H;
        for ( ; p->next != NULL; p = p->next);
        p->next = new_node;
        new_node->prev = p;
    }
    H->len++;
}
void show(node* H)
{
    if (H == NULL) return;
    if(empty_double(H)) return;
    node* p = H->next;
    for ( ; p; ) {
        printf("%d", p->data);
        p = p->next;
    }
    printf("\n");
}
//按位置插入
void insert_pos(node* H)
{
    if(H == NULL) return;
    int num, ele, j;
    node* z = H;
    for(j = 1; z->next != NULL; j++) z = z->next;
    printf("输入需要插入的位置：");
    scanf("%d", &num);
    if (num < 1 || num > j) {
        printf("插入位置不合理!\n");
        exit(1);
    }
    printf("输入需要插入的元素：");
    scanf("%d", &ele);
    node* p = H;
    node* q = creat_node(ele);
    for (int i = 0; i < num - 1; i++) p = p->next;
    q->next = p->next;
    q->prev = p;
    if (p->next != NULL) {
        p->next->prev = q;
    }
    p->next = q;
    H->len++;
}
//头删
void delete_head(node* H)
{
    if(H == NULL) return;
    if(empty_double(H)) return;
    node* p = H->next;
    if (p->next == NULL) H->next = NULL;
    else {
        H->next = p->next;
        p->next->prev = H;
    }
    free(p);
    p = NULL;
    H->len--;
}
//尾删
void delete_tail(node*H)
{
    if(H == NULL) return;
    if(empty_double(H)) return;
    node* p = H;
    node* q = H->next;
    for ( ; p->next != NULL; p = p->next) q = p;
    q->next = NULL;
    free(p);
    p = NULL;
    H->len--;
}
//按位置删除
void delete_pos(node* H)
{
    if(H == NULL) return;
    int num, j;
    node* z = H;
    for(j = 1; z->next != NULL; j++) z = z->next;
    printf("输入需要删除的位置：");
    scanf("%d", &num);
    if (num < 1 || num >= j) {
        printf("删除位置不合理!\n");
        exit(1);
    }
    node* p = H;
    for (int i = 0; i < num - 1; i++) {
        p = p->next;
    }
    node* q = p->next;
    if (q->next == NULL) {
        p->next = NULL;
        free(q);
        q = NULL;
    }
    else {
        p->next = q->next;
        p->next->prev = p;
        free(q);
        q = NULL;
    }
    H->len--;
}
//按位置查找
void find_pos(node* H)
{
    if(H == NULL) return;
    int num, j;
    node* z = H;
    for(j = 1; z->next != NULL; j++) z = z->next;
    printf("输入需要查找的位置：");
    scanf("%d", &num);
    if (num < 1 || num >= j) {
        printf("查找位置不合理!\n");
        exit(1);
    }
    node* p = H;
    for (int i = 0; i < num; i++) {
        p = p->next;
    }
    printf("当前位置元素为：%d\n", p->data);
}
void free_double(node* H)
{
    if (H == NULL) return;
    node* p = H;
    for ( ; p; ) {
        node* next_node = p->next;
        free(p);
        p = next_node;
    }
    printf("链表已释放\n");
}