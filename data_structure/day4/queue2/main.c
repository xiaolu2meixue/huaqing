#include "queue.h"

int main()
{
    Queue q;           // 在栈上创建队列结构体
    creat_Queue(&q);   // 初始化队列
    
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printQueue(&q);    // 输出: Queue: 10 20 30
    
    // 测试出队
    printf("Dequeue: %d\n", dequeue(&q));  // 输出: 10
    
    // 测试循环特性
    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60);   // 队列已满，无法添加
    printQueue(&q);    // 输出: Queue: 20 30 40 50
    
    return 0;
}