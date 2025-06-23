#include <stdio.h>
#include <stdlib.h>

// 队列节点结构
typedef struct QueueNode {
    int data;               // 存储数据
    struct QueueNode* next; // 指向下一个节点
} QueueNode;

// 队列结构
typedef struct {
    QueueNode* front; // 队头指针
    QueueNode* rear;  // 队尾指针
    int size;         // 队列大小
} LinkedQueue;

// 初始化队列
LinkedQueue* initQueue()
{
    LinkedQueue* queue = (LinkedQueue*)malloc(sizeof(LinkedQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// 判空
int isEmpty(LinkedQueue* queue)
{
    return queue->front == NULL;
}

// 入队
void enqueue(LinkedQueue* queue, int data)
{
    // 创建新节点
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    
    // 如果队列为空，新节点同时是队首和队尾
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // 否则添加到队尾
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    
    queue->size++;
    printf("入队: %d\n", data);
}

// 出队
int dequeue(LinkedQueue* queue)
{
    if (isEmpty(queue)) {
        printf("队列为空\n");
        return -1; // 返回错误值
    }
    
    QueueNode* temp = queue->front;
    int data = temp->data;
    
    // 移动队首指针
    queue->front = queue->front->next;
    
    // 如果队列只有一个元素，出队后队列为空
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp); // 释放原队首节点
    queue->size--;
    
    printf("出队: %d\n", data);
    return data;
}

// 获取队首元素（不删除）
int first(LinkedQueue* queue)
{
    if (isEmpty(queue)) {
        printf("队列为空!\n");
        return -1;
    }
    return queue->front->data;
}

// 获取队列大小
int getSize(LinkedQueue* queue) {
    return queue->size;
}

// 打印队列内容
void printQueue(LinkedQueue* queue)
{
    if (isEmpty(queue)) {
        printf("队列为空!\n");
        return;
    }
    
    printf("队列大小：%d: ", queue->size);
    QueueNode* current = queue->front;
    for ( ; current != NULL; ) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

// 销毁队列
void destroyQueue(LinkedQueue* queue)
{
    for ( ; !isEmpty(queue); ) {
        dequeue(queue);
    }
    free(queue);
    printf("队列已销毁\n");
}

int main()
{
    // 创建队列
    LinkedQueue* queue = initQueue();
    
    // 入队操作
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    printQueue(queue);
    
    // 查看队首
    printf("首元素: %d\n", first(queue));
    
    // 出队操作
    dequeue(queue);
    printQueue(queue);
    
    // 再次入队
    enqueue(queue, 40);
    enqueue(queue, 50);
    printQueue(queue);
    
    // 销毁队列
    destroyQueue(queue);
    
    return 0;
}