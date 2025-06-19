#pragma once

#include <myhead.h>

typedef struct tree {
    char data;
    struct tree* lchild;
    struct tree* rchild;
}tree;

tree* create_tree();
tree* create_node(char data);
void pre_show(tree* T);
void mid_show(tree* T);
void tail_show(tree* T);