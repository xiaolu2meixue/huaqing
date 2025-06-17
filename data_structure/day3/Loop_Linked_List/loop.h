#pragma once

#include <myhead.h>
#include <unistd.h>

typedef struct node {
    union {
        int data;
        int len;
    };
    struct node* next;
}node;
node* creat_loop();
node* creat_node(int value);
int empty_loop(node* H);
void insert_head(node* H, int value);
void insert_tail(node* H, int value);
void show_loop(node* H);
void delete_head(node* H);
void delete_tail(node* H);
void insert_pos(node* H);
void delete_pos(node* H);
void find_pos(node* H);
node* delete(node* H);
void show_no_head(node* H);