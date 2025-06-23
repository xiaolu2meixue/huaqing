#pragma once

#include <myhead.h>

typedef struct user {
    char username[15];
    char passwd[15];
}user;

// typedef struct 

user* regist();
int is_user();