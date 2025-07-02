#include <myhead.h>

int main()
{
    int num_children = 4;  // 创建4个子进程
    pid_t pid = 1; // 初始化pid为非零值

    printf("父进程 PID: %d\n", getpid());
    
    // 第一个子进程的创建
    if (pid > 0) { // 检查父进程
        pid = fork();
        if (pid == 0) {
            //sleep(1);
            printf("子进程 %d PID: %d\n", 0, getpid());
            sleep(1);
        }
    }

    // 创建多个子进程（进程扇）
    for (int i = 1; i < num_children; i++) {
        if (pid < 0) {
            ERRLOG("fork failed");
            exit(1);
        }
        else if (pid > 0) { // 父进程分支
            pid = fork();  // 创建子进程
            
            if (pid == 0) { // 子进程分支
                //sleep(1);
                printf("子进程 %d PID: %d\n", i, getpid());
                sleep(1);
            }
        }
        else break;
    }

    return 0;
}