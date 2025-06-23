#pragma once

#include <myhead.h>
#define NUM 5

typedef struct hashlist {
    int num;
    char* data;
}hashlist;

hashlist* init_hash();
int hash(int data);
void put_hash(hashlist* list, char data);
void print_hash(hashlist* list);