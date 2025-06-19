#include "queue.h"

// 初始化队列 - 只需重置指针
void creat_Queue(Queue* q)
{
    q->front = 0;
    q->rear = 0;
    memset(q->data, 0, sizeof(q->data));  // 可选：清零数据
}

// 检查队列是否为空
int isEmpty(Queue* q)
{
    return q->front == q->rear;
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
    Q->rear = (Q->rear + 1) % MAX;  // 循环移动
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
    Q->front = (Q->front + 1) % MAX;  // 循环移动
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
    while (i != Q->rear) {
        printf("%d ", Q->data[i]);
        i = (i + 1) % MAX;  // 循环遍历
    }
    printf("\n");
}