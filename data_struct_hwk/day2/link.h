#pragma once

#include <myhead.h>

typedef struct node {
    union {
        int data;
        int len;
    };
    struct node* next;
}node;

node* creat_link();
node* creat_node(int value);
int empty_link(node* H);
void insert_head(node* H, int value);
void insert_tail(node* H, int value);
void show_link(node* H);
void delete_head(node* H);
void delete_tail(node* H);
void delete_tail(node* H);
void insert_pos(node* H);
void delete_pos(node* H);
void find_pos(node* H);
void change_ele(node* H);
void invert_link(node* H);
void invert_link2(node* H);


