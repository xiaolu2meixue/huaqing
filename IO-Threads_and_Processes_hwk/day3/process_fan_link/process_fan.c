#include <myhead.h>

int main()
{
    int num_children = 4;  // 创建4个子进程
    pid_t pid;

    printf("父进程 PID: %d\n", getpid());

    // 创建多个子进程（进程扇）
    for (int i = 0; i < num_children; i++) {
        pid = fork();  // 创建子进程
        
        if (pid < 0) {
            ERRLOG("fork failed");
            exit(1);
        }
        else if (pid == 0) {
            // 子进程
            printf("子进程 %d PID: %d\n", i, getpid());
            sleep(2);
            exit(0);   // 子进程退出
        }
    }

    // 父进程等待所有子进程结束
    for (int i = 0; i < num_children; i++) wait(NULL);  // 阻塞等待任意子进程退出

    printf("所有子进程结束，父进程终止！\n");
    return 0;
}