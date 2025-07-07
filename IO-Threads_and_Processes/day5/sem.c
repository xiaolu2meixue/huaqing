#include <myhead.h>

// 库存信号量
sem_t sem1;
sem_t sem2;
sem_t sem3;

void* produce(void *arg)
{
    int num_loops = *(int *)arg;
    for (int i = 0 ; i < num_loops; i++) {
        sem_wait(&sem2);
        int num;
        sem_post(&sem1);
        sem_getvalue(&sem1, &num);
        printf("生产者:生产了一部手机！(现在有%d部手机)\n", num);
        sem_post(&sem3);    
    }
    return NULL;
}

void* consumer1(void *arg)
{
    int num_loops = *(int *)arg;
    for (int i = 0 ; i < num_loops; i++) {
        sem_wait(&sem3);
        int num;
        sem_wait(&sem1);
        sem_getvalue(&sem1, &num);
        printf("消费者1:消费了一部手机！(现在有%d部手机)\n", num);
        sem_post(&sem2);  
    }
    return NULL;
}

void* consumer2(void *arg)
{
    int num_loops = *(int *)arg;
    for (int i = 0 ; i < num_loops; i++) {
        sem_wait(&sem3);
        int num;
        sem_wait(&sem1);
        sem_getvalue(&sem1, &num);
        printf("消费者2:消费了一部手机！(现在有%d部手机)\n", num);
        sem_post(&sem2); 
    }
    return NULL;
}

int main()
{
    const int loops_per_thread1 = 10;
    const int loops_per_thread2 = 5;
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 1);
    sem_init(&sem3, 0, 0);
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    // 创建线程
    pthread_create(&thread1, NULL, produce, (void *)&loops_per_thread1);
    pthread_create(&thread2, NULL, consumer1, (void *)&loops_per_thread2);
    pthread_create(&thread3, NULL, consumer2, (void *)&loops_per_thread2);
    // 等待所有线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("结束生产与消费！\n");
    return 0;
}