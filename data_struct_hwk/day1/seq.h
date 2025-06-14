#pragma
#include <myhead.h>

typedef struct seq
{
    int* arr;
    int len;     //实际长度
    int max_len; //当前的最大长度
}seq;
enum {
    MYNULL = -1,
    SUSSES,
    EMPTY,
    FULL,
};

seq* creat_seq();
int empty_seq(seq* S);
int full_seq(seq* S);
void insert_head(int data, seq* S);
void insert_end(int data, seq* S);
void delete_end(seq* S);
void delete_start(seq* S);