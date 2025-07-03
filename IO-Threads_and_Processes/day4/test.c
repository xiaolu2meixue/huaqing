#include <myhead.h>

int main()
{
    pid_t pid = fork();
	if(pid == 0) {
		setsid();
		chdir("/");
		umask(0);
		for (int i = 0; i < getdtablesize(); i++) close(i);
		int oldfd = open("./my.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
		//把0、1、2文件描述符赋值给oldfd
		//终端输入输出写入oldfd对应文件中
		dup2(oldfd, 0);
		dup2(oldfd, 1);
		dup2(oldfd, 2);

		for ( ; ; ) {
			printf("这是一个子进程！\n");
			fflush(stdout);
			sleep(2);
		}
	}
	else if (pid == -1) ERRLOG("fork error..\n");

	//父进程
    return 0;
}