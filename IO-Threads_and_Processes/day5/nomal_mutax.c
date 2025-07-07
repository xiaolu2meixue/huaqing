#include <myhead.h>

int num; //临界区
pthread_mutex_t mutex1; // 互斥锁1
pthread_mutex_t mutex2; // 互斥锁2

void* produce(void *arg)
{
    int num_loops = *(int *)arg;
    for (int i = 0 ; i < num_loops; i++) {
        // 获取锁 (阻塞)
        pthread_mutex_lock(&mutex2);
        // 临界区开始
        num++;
        printf("生产者:生产了一部手机！(现在有%d部手机)\n", num);
        // 临界区结束
        // 释放锁
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

void* consumer(void *arg)
{
    int num_loops = *(int *)arg;
    for (int i = 0 ; i < num_loops; i++) {
        // 获取锁 (阻塞)
        pthread_mutex_lock(&mutex1);
        // 临界区开始
        num--;
        printf("消费者:消费了一部手机！(现在有%d部手机)\n", num);
        // 临界区结束
        // 释放锁
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

int main()
{
    const int loops_per_thread = 5;
    num = 0;
    pthread_t thread1;
    pthread_t thread2;

    // 初始化互斥锁 (属性NULL表示默认)
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    pthread_mutex_lock(&mutex1);

    // 创建线程
    pthread_create(&thread1, NULL, produce, (void *)&loops_per_thread);
    pthread_create(&thread2, NULL, consumer, (void *)&loops_per_thread);

    // 等待所有线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    printf("结束生产与消费！\n");
    return 0;
}