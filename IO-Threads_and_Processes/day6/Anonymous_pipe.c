#include <myhead.h>

int main(int argc, const char* argv[])
{
    //创建管道
    //pipefd[0]----读
    //pipefd[1]----写
    int pipefd[2];
    if (pipe(pipefd) == -1) ERRLOG("pipe error");
    //无名管道用于存在亲缘关系之间的进程通信，所以需要创建父子进程
    pid_t pid = fork();
    if (pid == -1) ERRLOG("fork error");
    else if (pid == 0) {
        close(pipefd[1]);
        char buf[128] = "";
        for( ; ; ) {
            memset(buf, 0, sizeof(buf));
            ssize_t res = read(pipefd[0], buf, sizeof(buf) - 1);
            if (res = 0) {
                printf("读取到文件末尾..\n");
                break;
            }
            else if (res == -1) ERRLOG("read error");
            if (strcmp(buf, "quit") == 0) {
                printf("子进程退出..\n");
                break;
            }
        printf("buf = [%s]\n", buf);
        }
    close(pipefd[0]);
    }
    else if (pid > 0) {
        close(pipefd[0]);
        for ( ; ; ) {
            char buf[128] = "";
            fgets(buf, sizeof(buf), stdin);
            buf[strcspn(buf, "\n")] = '\0';

            write(pipefd[1], buf, strlen(buf));
            if (strcmp(buf, "quit") == 0) {
                printf("父进程退出..\n");
                break;
            }
        }
        close(pipefd[1]);
    }
    return 0;
}