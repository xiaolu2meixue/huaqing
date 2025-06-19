#include "tree.h"

tree* create_tree()
{
    char data;
    scanf(" %c", &data);
    tree* T;
    if (data = '#') return NULL;
    T = create_node(data);
    T->lchild = create_tree();
    T->rchild = create_tree();
    return T;
}
tree* create_node(char data)
{
    tree* new = (tree*)malloc(sizeof(tree));
    if(new==NULL) return NULL;
    new->data = data;
    new->lchild = NULL;
    new->rchild = NULL;
    return new;
}
//3、前序遍历 根左右
void pre_show(tree* T)
{
    if (T == NULL) return;
    //输出根节点的数据
    printf("%c",T->data);
    //左子树也要前序遍历
    pre_show(T->lchild);
    //右子树也要前序遍历
    pre_show(T->rchild);
}
//4、中序遍历 左根右
void mid_show(tree* T)
{
    if (T == NULL) return;
    pre_show(T->lchild);
    printf("%c",T->data);
    pre_show(T->rchild);
}
//5、后序遍历 左右根
void tail_show(tree* T)
{
    if (T == NULL) return;
    pre_show(T->lchild);
    pre_show(T->rchild);
    printf("%c",T->data);
}