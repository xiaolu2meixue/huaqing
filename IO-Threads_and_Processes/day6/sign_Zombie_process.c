#include <myhead.h>
int count = 1;
void handler(int sig)
{
    pid_t pid;
    for( ; pid = waitpid(-1, NULL, 0) > 0; count++) printf("count = %d\n", count);
}
int main (int argc, const char* argv[])
{
    signal(SIGCHLD, handler);
    for(int i = 0; i < 50; i++) if(0 == fork()) exit(0);
    sleep(1);
    return 0;
}
