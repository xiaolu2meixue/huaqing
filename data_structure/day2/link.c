#include "link.h"
//申请单链表（头节点）
node* creat_link(){
    node* H = (node*)malloc(sizeof(node));
    if (H == NULL) {
        printf("申请内存失败\n");
        return NULL;
    }
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
    new_node->next = NULL;
    return new_node;
}
//判空
int empty_link(node* H)
{
    if (H == NULL) return -2;
    return H->next == NULL? 1: 0;
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
    for(; p->next != NULL; p = p->next);
    node* new = creat_node(value);
    p->next = new;
    //new->next = NULL;(新节点的指针域已经置空，无需重复操作)
}
//输出
void show_link(node* H)
{
    if (H == NULL) {
        printf("入参为空，请检查！");
        return;
    }
    node* p = H->next;
    for(; p != NULL; p = p->next) printf("%d", p->data);
    printf("\n");
}
//头删
void delete_head(node* H)
{
    if(H == NULL) return;
    if(empty_link(H)) return;
    node* p = H->next;
    H->next = p->next;
    free(p);
}
//尾删
void delete_tail(node* H)
{
    if (empty_link(H)) {
        printf("链表为空，无需删除");
        return;
    }
    if(H == NULL) return;
    if(empty_link(H)) return;
    node* p = H;
    node* q = H->next;
    for(; q->next != NULL; q = q->next) p = q;
    p->next = NULL;
    free(q);
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
    for(j = 1; z->next != NULL; j++) z = z->next;
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
//按值修改
void change_ele(node* H)
{
    int num, ele;
    if(H == NULL) return;
    printf("输入需要查找的元素：");
    scanf("%d", &num);
    printf("输入需要改成的元素：");
    scanf("%d", &ele);
    node* p = H;
    for (; p != NULL; p = p->next) if (p->data == num) p->data = ele;
}
//单项链表的逆置
void invert_link(node* H)
{
    if (H == NULL || H->next == NULL) {
        return;
    }
    int* arr = (int*)malloc(sizeof(int) * H->len);
    if (arr == NULL) {
        printf("内存分配失败\n");
        return;
    }
    int* start = arr;
    int* end = arr + H->len - 1;
    node* p = H->next;
    //将所有数据域数据赋值给数组
    for (; start <= end; p = p->next) *start++ = p->data;
    start = arr;
    p = H->next;
    //反转数组
    for (; start <= end; ) {
        int temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
    end = arr + H->len - 1;
    start = arr;
    //将数组元素重新赋值给链表
    for (; start <= end; p = p->next) p->data = *start++;
    free(arr);
    arr = NULL;
}
void invert_link2(node* H)
{
    if (H == NULL || H->next == NULL) {
        return;
    }
    node* p = H->next;  //断开表头
    node* q = NULL;
    H->next = NULL;     //链表头指针域指空
    for (; p != NULL; ) {
        q = p; //保存P
        p = p->next;  //向后遍历
        q->next = H->next; //断开q
        H->next = q;  //头插
    }

}
