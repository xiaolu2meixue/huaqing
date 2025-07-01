#include <myhead.h>
int main(int argc, const char *argv[])
{
    umask(0);
	int fd = open("my.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (-1 == fd) ERRLOG("open error");

    int a = 100;
    char buf[128] = "";
    snprintf(buf, sizeof(buf), "%d", a);
    ssize_t res = write(fd, buf, strlen(buf));
    if (res == -1) ERRLOG("write error");

    if (lseek(fd, 0, SEEK_SET) == (off_t)-1) ERRLOG("lseek error");
    
    memset(buf, 0, sizeof(buf));
    ssize_t bytes = read(fd, buf, sizeof(buf));
    if (bytes == -1) ERRLOG("read error");
    printf("File content: %s\n", buf);

    if (-1 == close(fd)) ERRLOG("close error");

	return 0;
}