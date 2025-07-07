#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5    // 缓冲区大小
#define ITEMS_TO_PRODUCE 10 // 生产者生产的总项目数
#define ITEMS_TO_CONSUME 10 // 消费者消费的总项目数

// 共享资源
int buffer[BUFFER_SIZE]; // 缓冲区
int count = 0;           // 当前缓冲区中的项目数
int in = 0;              // 生产者放入位置
int out = 0;             // 消费者取出位置

// 同步工具
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 互斥锁
pthread_cond_t cond_full = PTHREAD_COND_INITIALIZER;  // 缓冲区满条件
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER; // 缓冲区空条件

// 生产者函数
void *producer(void *arg) {
    for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
        // 生产一个项目
        int item = rand() % 100;

        // 获取互斥锁
        pthread_mutex_lock(&mutex);
        
        // 如果缓冲区满，等待
        while (count == BUFFER_SIZE) {
            printf("生产者: 缓冲区满，等待中...\n");
            pthread_cond_wait(&cond_full, &mutex);
        }
        
        // 放入缓冲区
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        
        printf("生产者: 生产 %d (缓冲区: %d/5)\n", item, count);
        
        // 通知消费者缓冲区非空
        pthread_cond_signal(&cond_empty);
        
        // 释放锁
        pthread_mutex_unlock(&mutex);
        
        // 模拟生产时间
        usleep(100000); // 0.1秒
    }
    
    printf("生产者: 完成生产 %d 个项目\n", ITEMS_TO_PRODUCE);
    return NULL;
}

// 消费者函数
void *consumer(void *arg) {
    for (int i = 0; i < ITEMS_TO_CONSUME; i++) {
        // 获取互斥锁
        pthread_mutex_lock(&mutex);
        
        // 如果缓冲区空，等待
        while (count == 0) {
            printf("消费者: 缓冲区空，等待中...\n");
            pthread_cond_wait(&cond_empty, &mutex);
        }
        
        // 从缓冲区取出项目
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        
        printf("消费者: 消费 %d (缓冲区: %d/5)\n", item, count);
        
        // 通知生产者缓冲区非满
        pthread_cond_signal(&cond_full);
        
        // 释放锁
        pthread_mutex_unlock(&mutex);
        
        // 模拟消费时间
        usleep(150000); // 0.15秒
    }
    
    printf("消费者: 完成消费 %d 个项目\n", ITEMS_TO_CONSUME);
    return NULL;
}

int main()
{
    pthread_t producer_thread, consumer_thread;
    
    printf("===== 简化版生产者-消费者模型 =====\n");
    printf("缓冲区大小: %d\n", BUFFER_SIZE);
    printf("计划生产: %d 个项目\n", ITEMS_TO_PRODUCE);
    printf("计划消费: %d 个项目\n\n", ITEMS_TO_CONSUME);
    
    // 创建生产者和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // 等待线程完成
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    printf("\n===== 程序结束 =====\n");
    return 0;
}