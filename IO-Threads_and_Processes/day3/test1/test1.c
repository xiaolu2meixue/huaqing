#include <myhead.h>
int main(int argc, const char *argv[])
{
	pid_t pid = fork();
	if (pid > 0) {
		printf("pid = %d, ppid = %d, _%d_\n", getpid(), getppid(), __LINE__);
		printf("pid = %d\n", getpid());
		_exit(0);
		for( ; ; ) {
			printf("这是父进程..\n");
			sleep(3);
		}
	}
	else if (pid == 0) {
		printf("pid = %d, ppid = %d, _%d_\n", getpid(), getppid(), __LINE__);
		fflush(stdout);
		for ( ; ; ) {
			printf("这是子进程..\n");
			printf("pid = %d\n", getpid());
			sleep(3);
		}
	}
	else ERRLOG("fork error!");
	for( ; ; );
	return 0;
}
