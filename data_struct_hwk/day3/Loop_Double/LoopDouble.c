#include "LoopDouble.h"

//相比于基本的删除和插入，此程序的删除和插入位置若不合理，不会继续打印原链表并释放原链表堆内存
//并且此程序循环打印链表只打印12个数，打印结束后会释放堆内存，解决了死循环打印无法释放堆内存的问题

//申请双链表（头节点）
node* creat_loop_double()
{
    node* H = (node*)malloc(sizeof(node));
    if (H == NULL) {
        printf("申请内存失败\n");
        return NULL;
    }
    H->prev = H;
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
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}
//判空
int empty_loop_double(node* H)
{
    if (H == NULL) return -2;
    return H->next == H? 1: 0;
}
void insert_head(node* H, int value)
{
    node* new_node = creat_node(value);
    //新结点的后继保存原来头结点的后继
    new_node->next = H->next;
    //新结点的前驱指向头结点
    new_node->prev = H;
    //头结点后继节点的前驱指向新结点
    if (H->next != H) {
        H->next->prev = new_node;
    }
    else H->prev = new_node;
    //头结点的后继指向新结点
    H->next = new_node;
    H->len++;
}
void insert_tail(node* H, int value)
{
    node* new_node = creat_node(value);
    if (H->next == H) {  
        H->next = new_node;
        new_node->prev = H;
    }
    else {
        node* p = H;
        for ( ; p->next != H; p = p->next);
        p->next = new_node;
        new_node->prev = p;
    }
    new_node->next = H;
    H->prev = new_node;
    H->len++;
}
//删除头节点
node* delete(node* H)
{
    if(H == NULL) return NULL;
    node* p = H->next;
    node* q = H->next;
    for(; q->next != H; q = q->next);
    q->next = p;
    p->prev = q;
    free(H);
    H = NULL;
    return p;
}
//删除头节点后单项循环列表的输出
void show_no_head(node* H)
{
    node* p = H;
    for(int i = 0; i < 12; p = p->next, i++) {
        sleep(1);
        printf("%d ", p->data);
        fflush(stdout);  //默认是行缓冲的，如果未换行可能不会立即显示。可以强制刷新
    }
    printf("\n");
}
//按位置插入
int insert_pos(node* H)
{
    if(H == NULL) return 2;
    int num, ele, j;
    node* z = H;
    for(j = 1; z->next != H; j++) z = z->next;
    printf("输入需要插入的位置：");
    scanf("%d", &num);
    if (num < 1 || num > j) {
        printf("插入位置不合理!\n");
        return 1;
    }
    else {
        printf("输入需要插入的元素：");
        scanf("%d", &ele);
        node* p = H;
        node* q = creat_node(ele);
        for (int i = 0; i < num - 1; i++) p = p->next;
        q->next = p->next;
        q->prev = p;
        if (p->next != H) {
            p->next->prev = q;
        }
        p->next = q;
        H->len++;
        return 0;
    }
}
//头删
void delete_head(node* H)
{
    if(H == NULL) return;
    if(empty_loop_double(H)) return;
    node* p = H->next;
    if (p->next == H) H->next = H;
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
    if(empty_loop_double(H)) return;
    node* p = H;
    node* q = H->next;
    for ( ; p->next != H; p = p->next) q = p;
    q->next = H;
    free(p);
    p = NULL;
    H->len--;
}
//按位置删除
int delete_pos(node* H)
{
    if(H == NULL) return 2;
    int num, j;
    node* z = H;
    for(j = 1; z->next != H; j++) z = z->next;
    printf("输入需要删除的位置：");
    scanf("%d", &num);
    if (num < 1 || num >= j) {
        printf("删除位置不合理!\n");
        return 1;
    }
    else {
        node* p = H;
        for (int i = 0; i < num - 1; i++) {
            p = p->next;
        }
        node* q = p->next;
        if (q->next == H) {
            p->next = H;
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
        return 0;
    }
}
//按位置查找
void find_pos(node* H)
{
    if(H == NULL) return;
    int num, j;
    node* z = H;
    for(j = 1; z->next != H; j++) z = z->next;
    printf("输入需要查找的位置：");
    scanf("%d", &num);
    if (num < 1 || num >= j) {
        printf("查找位置不合理,请输入0 ~ %d!\n", j - 1);
    }
    else {
        node* p = H;
        for (int i = 0; i < num; i++) {
        p = p->next;
        }
        printf("当前位置元素为：%d\n", p->data);
    }
}
void free_loop_double(node* H)
{
    if (H == NULL) return;
    node* p = H;
    node* next_node = p->next;
    free(p);
    p = next_node;
    for ( ; p->next != H->next; ) {
        next_node = p->next;
        free(p);
        p = next_node;
    }
    printf("链表已释放\n");
}