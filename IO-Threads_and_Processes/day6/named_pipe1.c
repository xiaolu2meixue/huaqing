#include <myhead.h>

int main(int argc, const char* argv[])
{
    //创建有名管道
    umask(0);
    if (mkfifo("./hello", 0777) == -1 && errno != EEXIST) ERRLOG("mkfifo error");
    printf("fifo susses\n");
    int fd = open("./hello", O_WRONLY);
    for( ; ; ) {
        char buf[128] = "";
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        write(fd, buf, strlen(buf));
        if (strcmp(buf, "quit") == 0) {
            printf("父进程退出..\n");
            break;
        }
    }
    close(fd);
    return 0;
}