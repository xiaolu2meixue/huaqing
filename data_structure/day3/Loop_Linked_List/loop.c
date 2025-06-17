#include "loop.h"
//申请单链表（头节点）
node* creat_loop(){
    node* H = (node*)malloc(sizeof(node));
    if (H == NULL) {
        printf("申请内存失败\n");
        return NULL;
    }
    H->next = H;
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
    new_node->next = NULL;
    return new_node;
}
//判空
int empty_loop(node* H)
{
    if (H == NULL) return -2;
    return H->next == H? 1: 0;
}
//头插
void insert_head(node* H, int value)
{
    if (H == NULL) {
        printf("入参为空，请检查！");
        return;
    }
    node* new = creat_node(value);
    new->next = H->next;
    H->next = new;
    H->len++;
}
//尾插
void insert_tail(node* H, int value)
{
    if (H == NULL) {
        printf("入参为空，请检查！");
        return;
    }
    node* p = H;
    for(; p->next != H; p = p->next);
    node* new = creat_node(value);
    p->next = new;
    new->next = H;
}
//输出
void show_loop(node* H)
{
    if (H == NULL) {
        printf("入参为空，请检查！");
        return;
    }
    node* p = H->next;
    for(; ; p = p->next) {
        if (p == H) continue;
        sleep(1);
        printf("%d ", p->data);
        fflush(stdout);  //默认是行缓冲的，如果未换行可能不会立即显示。可以强制刷新
    }
    printf("\n");
}
//头删
void delete_head(node* H)
{
    if(H == NULL) return;
    if(empty_loop(H)) return;
    node* p = H->next;
    H->next = p->next;
    free(p);
}
//尾删
void delete_tail(node* H)
{
    if (empty_loop(H)) {
        printf("链表为空，无需删除");
        return;
    }
    if(H == NULL) return;
    node* p = H;
    node* q = H->next;
    for(; q->next != H; q = q->next) p = q;
    p->next = H;
    free(q);
}
//删除头节点
node* delete(node* H)
{
    if(H == NULL) return NULL;
    node* p = H->next;
    node* q = H->next;
    for(; q->next != H; q = q->next);
    q->next = p;
    free(H);
    H = NULL;
    return p;
}
//删除头节点后单项循环列表的输出
void show_no_head(node* H)
{
    node* p = H;
    for(; ; p = p->next) {
        sleep(1);
        printf("%d ", p->data);
        fflush(stdout);  //默认是行缓冲的，如果未换行可能不会立即显示。可以强制刷新
    }
    printf("\n");
}
//按位置插入
void insert_pos(node* H)
{
    if(H == NULL) return;
    int num, ele, j;
    node* z = H;
    for(j = 1; z->next != H; j++) z = z->next;
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
    for (int i = 0; i < num - 1; i++) {
        p = p->next;
    }
    q->next = p->next;
    p->next = q;
}
//按位置删除
void delete_pos(node* H)
{
    if(H == NULL) return;
    int num, j;
    node* z = H;
    for(j = 1; z->next != H; j++) z = z->next;
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
    node* pos = p->next;
    p->next = pos->next;
    free(pos);
}
//按位置查找(注释部分为按位置修改)
void find_pos(node* H)
{
    if(H == NULL) return;
    int num, j;
    //int ele;
    node* z = H;
    for(j = 1; z->next != H; j++) z = z->next;
    printf("输入需要查找的位置：");
    scanf("%d", &num);
    if (num < 1 || num >= j) {
        printf("查找位置不合理!\n");
        exit(1);
    }
    // printf("输入需要修改成的元素：");
    // scanf("%d", &ele);
    node* p = H;
    for (int i = 0; i < num; i++) {
        p = p->next;
    }
    //p->data = ele;
    printf("当前位置元素为：%d\n", p->data);
}