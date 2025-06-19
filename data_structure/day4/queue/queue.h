#pragma once

#include <myhead.h>
#define MAX 8

typedef struct {
    int data[MAX];
    int front;  // 队头索引
    int rear;   // 队尾索引（指向下一个插入位置）
} Queue;

void create_Queue(Queue *q);
int isEmpty(Queue* Q);
int isFull(Queue* Q);
int enqueue(Queue* Q, int value);
int dequeue(Queue* Q);
void printQueue(Queue* Q);