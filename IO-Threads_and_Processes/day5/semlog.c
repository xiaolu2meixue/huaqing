#include <myhead.h>

typedef struct Msg {
    sem_t* sem;
    int num;
}msg;

void* callback(void *arg)
{
    msg message = *(msg *)arg;
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

int main()
{
    sem_t sem;
    sem_init(&sem, 0, 3);
    msg buf[6];
    
    // 创建6个线程
    pthread_t thread[6];
    for (int i = 0; i < 6; i++)
    {
        buf[i].sem = &sem;
        buf[i].num = i + 1;
        pthread_create(&thread[i], NULL, callback, (void *)&buf[i]);
    }
    
    
    // 等待所有线程结束mmmmcvvvvvvv,vmnc     
    for (int i = 0; i < 6; i++)
    {
        pthread_join(thread[i], NULL);
    }
    

    printf("结束生产与消费！\n");
    return 0;
}