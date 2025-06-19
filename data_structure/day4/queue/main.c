#include "queue.h"

int main()
{
    Queue* q;
    create_Queue(q);
    
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    printQueue(q);  // 输出: Queue: 10 20 30
    return 0;
}