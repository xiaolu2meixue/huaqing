#pragma once

#include <myhead.h>

typedef struct node {
    int data;
    struct node* next;
}node;

node* create_node(int value);
int empty_stack(node** S);
void push_stack(node** S, int value);
void print_stack(node** S);