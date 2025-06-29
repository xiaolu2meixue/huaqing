#pragma once

#include <myhead.h>

typedef struct user {
    char username[15];
    char passwd[15];
}user;

typedef struct person {
    char name[15];
    char phone[15];
}person;

typedef struct adress_node {
    union {
        person data;
        int len;
    };
    struct adress_node* next;
}node;

//menu.c 内的函数
user* regist();
int is_user();
void p_menu();
int main_menu(node* H);
void show_all(node* H);
void delete(node* H);
void search(node* H);
void change(node* H);

//common.c 内的函数
node* creat_link();
node* creat_node(person value);
int empty_link(node* H);
void insert_tail(node* H, person value);
void free_list(node* H);
