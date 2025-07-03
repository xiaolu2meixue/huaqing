#include <myhead.h>

void* print_message(void *msg)
{
    char *message = (char *)msg;
    printf("分支线程 [TID:%lu] 开始执行\n", pthread_self());
    for ( ; ; ) {
        printf("\n分支线程消息: %s\n\n", message);
        sleep(2);
    }
    printf("分支线程 [TID:%lu] 结束\n", pthread_self());
    pthread_exit(NULL);
}

int main(int argc, const char* argv[])
{
    printf("主线程 [TID:%lu] 启动\n", pthread_self());
    
    pthread_t thread_id;
    char *message = "我是主进程传递过来的参数!";

    // 创建线程
    printf("主线程正在创建分支线程...\n");
    int ret = pthread_create(
        &thread_id,   // 存储线程ID
        NULL,         // 默认属性
        print_message,// 线程函数
        (void *)message // 参数
    );

    if (ret != 0) ERRLOG("创建线程失败");
    
    printf("主线程创建了分支线程 [TID:%lu]\n", thread_id);
    printf("主线程继续运行中...\n");
    sleep(4);

    // 等待线程结束
    printf("主线程等待分支线程结束...\n");
    sleep(4);
    printf("主线程等待分支线程结束... (怎么还没结束？)\n");
    sleep(4);
    printf("主线程等待分支线程结束... (坏了，分支线程死循环了！)\n");
    pthread_join(thread_id, NULL);
    
    printf("主线程 [TID:%lu] 结束\n", pthread_self());
    return 0;
}