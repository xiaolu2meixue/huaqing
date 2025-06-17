#pragma once

#include <myhead.h>
#include <unistd.h>

typedef struct node {
    union {
        int data;
        int len;
    };
    struct node* prev;
    struct node* next;
}node;

node* creat_loop_double();
node* creat_node(int value);
int empty_loop_double(node* H);
void insert_head(node* H, int value);
void insert_tail(node* H, int value);
node* delete(node* H);
void show_no_head(node* H);
//void show(node* H);
int insert_pos(node* H);
void delete_head(node* H);
void delete_tail(node*H);
int delete_pos(node* H);
void find_pos(node* H);
void free_loop_double(node* H);