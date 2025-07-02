#include <myhead.h>

int main()
{
    int chain_length = 5;  // 进程链长度（包含初始进程）
    pid_t pid;
    int current_level = 0;

    printf("初始进程 (第%d级进程) PID: %d\n", current_level, getpid());

    // 创建进程链
    for (int i = 0; i < chain_length - 1; i++) {
        pid = fork();  // 创建子进程
        
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0) {
            // 子进程代码
            current_level++;
            printf("子进程 (第%d级进程) PID: %d, 父进程 PID: %d\n", 
                   current_level, getpid(), getppid());
        }
        else {
            // 父进程等待直接子进程结束
            wait(NULL);
            break;  // 父进程不再继续创建更多子进程
        }
    }

    if (current_level == 4) printf("位于进程链尾 (第%d级进程) PID: %d\n", current_level, getpid());
    return 0;
}