#include <myhead.h>

#define FIFO_PATH "/tmp/myfifo_example"

int main()
{
    umask(0);
    // 创建有名管道 (FIFO)
    if (mkfifo(FIFO_PATH, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    
    if (pid == -1)  ERRLOG("fork failed");

    // 子进程 - 读取端
    if (pid == 0) { 
        printf("Child process (Reader) started. PID: %d\n", getpid());
        
        // 打开FIFO (阻塞直到写入端打开)
        int read_fd = open(FIFO_PATH, O_RDONLY);
        if (read_fd == -1) {
            perror("Child: open FIFO failed");
            exit(EXIT_FAILURE);
        }

        char buffer[256];
        ssize_t res;
        
        printf("Child waiting for messages...\n");
        while ((res = read(read_fd, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[res] = '\0';
            printf("Child received: %s", buffer);
            
            // 检查退出指令
            if (strcmp(buffer, "exit") == 0) {
                break;
            }
        }

        if (res == -1) ERRLOG("Child: read error");

        close(read_fd);
        printf("Child process exiting.\n");
        exit(EXIT_SUCCESS);    
    }
    // 父进程 - 写入端
    else {
        printf("Parent process (Writer) started. PID: %d\n", getpid());
        
        // 给子进程时间打开读取端
        sleep(1);
        
        // 打开FIFO
        int write_fd = open(FIFO_PATH, O_WRONLY);
        if (write_fd == -1) {
            perror("Parent: open FIFO failed");
            exit(EXIT_FAILURE);
        }

        char input[256];
        printf("Parent ready. Type messages (enter 'exit' to quit):\n");
        
        while (1) {
            printf("> ");
            fflush(stdout);
            
            if (!fgets(input, sizeof(input), stdin)) {
                perror("fgets failed");
                break;
            }
            
            // 写入管道
            if (write(write_fd, input, strlen(input)) == -1) {
                perror("Parent: write failed");
                break;
            }
            
            // 检查退出指令
            if (strcmp(input, "exit\n") == 0) {
                break;
            }
        }

        close(write_fd);
        
        // 等待子进程结束
        int status;
        waitpid(pid, &status, 0);
        printf("Parent waited for child. Exit status: %d\n", status);
        
        // 清理FIFO文件
        if (unlink(FIFO_PATH) == -1) {
            perror("unlink FIFO failed");
        } else {
            printf("FIFO file removed\n");
        }
        
        printf("Parent process exiting.\n");
    }

    return EXIT_SUCCESS;
}