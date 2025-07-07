#include <myhead.h> // 包含必要的头文件

void handler(int sig)
{
    printf("%d信号被捕获..\n", sig);
}

int main(int argc, const char* argv[])
{
    int pipe_fd[2]; // 管道文件描述符
    char buffer[] = "测试数据";
    
    // 注册信号处理函数
    if(SIG_ERR == signal(SIGPIPE, handler)) 
        ERRLOG("SIGPIPE signal error");
    
    printf("===== SIGPIPE信号捕获演示 =====\n");
    printf("当前进程ID: %d\n", getpid());
    
    // 1. 创建管道
    if(pipe(pipe_fd)) ERRLOG("pipe create error");
    printf("管道创建成功: 读端fd=%d, 写端fd=%d\n", pipe_fd[0], pipe_fd[1]);
    
    // 2. 关闭管道的读端 - 这将导致管道破裂
    printf("关闭管道读端(fd=%d)...\n", pipe_fd[0]);
    close(pipe_fd[0]);
    
    // 3. 尝试向管道写入数据 - 将触发SIGPIPE
    printf("\n尝试写入已关闭的管道...\n");
    ssize_t bytes_written = write(pipe_fd[1], buffer, sizeof(buffer));
    
    // 4. 检查写入结果
    if(bytes_written == -1) {
        if(errno == EPIPE) {
            printf("写入失败: 管道破裂 (EPIPE)\n");
        } else {
            perror("写入失败");
        }
    } else {
        printf("成功写入 %zd 字节\n", bytes_written);
    }
    
    // 5. 清理资源
    close(pipe_fd[1]);
    printf("\n程序结束\n");
    
    return 0;
}