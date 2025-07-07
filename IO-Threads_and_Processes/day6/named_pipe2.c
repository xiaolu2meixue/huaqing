#include <myhead.h>

int main(int argc, const char* argv[])
{
    //创建有名管道
    umask(0);
    if (mkfifo("./hello", 0777) == -1 && errno != EEXIST) ERRLOG("mkfifo error");
    printf("fifo susses");
    int fd = open("./hello", O_RDONLY);
    char buf[128] = "";
    for( ; ; ) {
        memset(buf, 0, sizeof(buf));
        ssize_t res = read(fd, buf, sizeof(buf)-1);
        if (res < 0) ERRLOG("read error");
        else if (res == 0) {
            printf("读取到文件结尾..\n");
            break;
        }
        if (strcmp(buf, "quit") == 0) {
            printf("子进程退出..\n");
            break;
        }
        printf("buf = [%s]\n", buf);
    }
    close(fd);
    return 0;
}