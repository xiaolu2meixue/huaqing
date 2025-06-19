// queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include <myhead.h>

#define MAX 5  // 定义队列最大容量

typedef struct {
    int front;      // 队头索引
    int rear;       // 队尾索引
    int data[MAX];  // 存储数据的数组
} Queue;

// 初始化队列（不再动态分配内存）
void creat_Queue(Queue* q);

// 检查队列是否为空
int isEmpty(Queue* q);

// 检查队列是否已满
int isFull(Queue* Q);

// 入队操作
int enqueue(Queue* Q, int value);

// 出队操作
int dequeue(Queue* Q);

// 打印队列
void printQueue(Queue* Q);

#endif