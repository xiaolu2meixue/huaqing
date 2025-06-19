#include "queue.h"

// 初始化队列
void create_Queue(Queue* Q)
{
    Q = (Queue*)malloc(sizeof(Queue));
    if (Q == NULL) return;
    memset(Q, 0, sizeof(Queue));
}
// 检查队列是否为空
int isEmpty(Queue* Q)
{
    return Q->front == Q->rear;
}

// 判满
int isFull(Queue* Q)
{
    return (Q->rear + 1) % MAX == Q->front;
}

// 入队
int enqueue(Queue* Q, int value)
{
    if (isFull(Q)) {
        printf("Queue is full!\n");
        return -1;
    }
    Q->data[Q->rear] = value;
    Q->rear = (Q->rear + 1) % MAX;
    return 0;
}

// 出队
int dequeue(Queue* Q)
{
    if (isEmpty(Q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int ret = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX;
    return ret;
}

// 打印队列
void printQueue(Queue* Q)
{
    if (isEmpty(Q)) {
        printf("Queue is empty\n");
        return;
    }
    int i = Q->front;
    printf("Queue: ");
    for ( ; i != Q->rear; i = (i + 1) % MAX) printf("%d ", Q->data[i]);
    printf("\n");
}
