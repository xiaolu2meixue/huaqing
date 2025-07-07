#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5    // 缓冲区大小
#define PRODUCE_ITEMS 15 // 生产者生产的总项目数
#define CONSUME_ITEMS 15 // 消费者消费的总项目数

// 共享缓冲区结构
typedef struct {
    int buffer[BUFFER_SIZE]; // 缓冲区数组
    int count;               // 当前缓冲区中的项目数
    int in;                  // 生产者放入位置
    int out;                 // 消费者取出位置
    pthread_mutex_t mutex;   // 互斥锁保护缓冲区
    pthread_cond_t cond_full;    // 条件变量：缓冲区满
    pthread_cond_t cond_empty;   // 条件变量：缓冲区空
} Buffer;

Buffer shared_buffer; // 全局共享缓冲区

// 初始化缓冲区
void buffer_init(Buffer *b) {
    b->count = 0;
    b->in = 0;
    b->out = 0;
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->cond_full, NULL);
    pthread_cond_init(&b->cond_empty, NULL);
}

// 销毁缓冲区资源
void buffer_destroy(Buffer *b) {
    pthread_mutex_destroy(&b->mutex);
    pthread_cond_destroy(&b->cond_full);
    pthread_cond_destroy(&b->cond_empty);
}

// 生产者函数
void *producer(void *arg) {
    int produced = 0;
    
    while (produced < PRODUCE_ITEMS) {
        // 生产一个项目
        int item = rand() % 100; // 生成0-99的随机数
        
        // 获取互斥锁
        pthread_mutex_lock(&shared_buffer.mutex);
        
        // 等待缓冲区有空间（使用while防止虚假唤醒）
        while (shared_buffer.count == BUFFER_SIZE) {
            printf("生产者: 缓冲区满，等待...\n");
            pthread_cond_wait(&shared_buffer.cond_full, &shared_buffer.mutex);
        }
        
        // 将项目放入缓冲区
        shared_buffer.buffer[shared_buffer.in] = item;
        shared_buffer.in = (shared_buffer.in + 1) % BUFFER_SIZE;
        shared_buffer.count++;
        produced++;
        
        printf("生产者: 生产项目 %d (缓冲区大小: %d)\n", item, shared_buffer.count);
        
        // 唤醒等待的消费者（可能有消费者在等待数据）
        pthread_cond_signal(&shared_buffer.cond_empty);
        
        // 释放互斥锁
        pthread_mutex_unlock(&shared_buffer.mutex);
        
        // 模拟生产时间
        usleep(rand() % 300000); // 0-0.3秒
    }
    
    printf("生产者: 完成生产 %d 个项目\n", PRODUCE_ITEMS);
    return NULL;
}

// 消费者函数
void *consumer(void *arg) {
    int consumed = 0;
    
    while (consumed < CONSUME_ITEMS) {
        // 获取互斥锁
        pthread_mutex_lock(&shared_buffer.mutex);
        
        // 等待缓冲区有数据（使用while防止虚假唤醒）
        while (shared_buffer.count == 0) {
            printf("消费者: 缓冲区空，等待...\n");
            pthread_cond_wait(&shared_buffer.cond_empty, &shared_buffer.mutex);
        }
        
        // 从缓冲区取出项目
        int item = shared_buffer.buffer[shared_buffer.out];
        shared_buffer.out = (shared_buffer.out + 1) % BUFFER_SIZE;
        shared_buffer.count--;
        consumed++;
        
        printf("消费者: 消费项目 %d (缓冲区大小: %d)\n", item, shared_buffer.count);
        
        // 唤醒等待的生产者（可能有生产者在等待空间）
        pthread_cond_signal(&shared_buffer.cond_full);
        
        // 释放互斥锁
        pthread_mutex_unlock(&shared_buffer.mutex);
        
        // 模拟消费时间
        usleep(rand() % 400000); // 0-0.4秒
    }
    
    printf("消费者: 完成消费 %d 个项目\n", CONSUME_ITEMS);
    return NULL;
}

int main()
{
    pthread_t prod_thread, cons_thread;
    
    // 初始化缓冲区
    buffer_init(&shared_buffer);
    
    printf("===== 生产者-消费者模型启动 =====\n");
    printf("缓冲区大小: %d\n", BUFFER_SIZE);
    printf("计划生产: %d 个项目\n", PRODUCE_ITEMS);
    printf("计划消费: %d 个项目\n\n", CONSUME_ITEMS);
    
    // 创建生产者和消费者线程
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    
    // 等待线程完成
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);
    
    // 清理资源
    buffer_destroy(&shared_buffer);
    
    printf("\n===== 生产者-消费者模型结束 =====\n");
    return 0;
}