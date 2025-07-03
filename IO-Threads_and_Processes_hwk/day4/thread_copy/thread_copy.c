#include <myhead.h>

#define BLOCK_SIZE 4096 // 分块大小

//建立结构体，用于传递必要参数到分支进程
typedef struct Message {
    const char* argv1;
    const char* argv2;
    off_t mid;
}message;

void* print_message(void *msg)
{
    message* mymessage = (message*)msg;
    const char *src_path = mymessage->argv1;
    const char *dest_path = mymessage->argv2;
    int child_src_fd = open(src_path, O_RDONLY);
        int child_dest_fd = open(dest_path, O_WRONLY);
        if (child_src_fd == -1 || child_dest_fd == -1) {
            perror("child open");
            pthread_exit(NULL);
        }

        // 定位到中点位置
        if (lseek(child_src_fd, mymessage->mid, SEEK_SET) == -1 || lseek(child_dest_fd, mymessage->mid, SEEK_SET) == -1) {
            perror("child lseek");
            pthread_exit(NULL);
        }

        // 分块拷贝
        char buf[BLOCK_SIZE];
        ssize_t nread;
        while ((nread = read(child_src_fd, buf, BLOCK_SIZE))) {
            if (nread == -1) {
                perror("child read");
                break;
            }
            if (nread == 0) break;

            if (write(child_dest_fd, buf, nread) != nread) {
                perror("child write");
                break;
            }
        }

        close(child_src_fd);
        close(child_dest_fd);
        printf("分支进程结束，后半部分拷贝完毕！\n");
        pthread_exit(NULL);
}

int main(int argc, const char* argv[])
{
    printf("主线程 [TID:%lu] 启动\n", pthread_self());
    
    pthread_t thread_id;
    message* mymessage = (message*)malloc(sizeof(message));

    if (argc != 3) {
        fprintf(stderr, "用法: %s <源文件> <目标文件>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    mymessage->argv1 = argv[1];
    mymessage->argv2 = argv[2];
    const char *src_path = argv[1];
    const char *dest_path = argv[2];

    // 打开源文件
    int src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) {
        perror("open source");
        pthread_exit(NULL);
    }

    // 获取文件大小
    off_t file_size = lseek(src_fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("lseek");
        close(src_fd);
        pthread_exit(NULL);
    }

    // 计算中点位置
    mymessage->mid = file_size / 2;
    
    // 重置文件偏移到开头
    if (lseek(src_fd, 0, SEEK_SET) == -1) {
        perror("lseek reset");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // 创建目标文件
    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("open destination");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    if (lseek(src_fd, 0, SEEK_SET) == -1 || lseek(dest_fd, 0, SEEK_SET) == -1) {
            perror("parent lseek");
            exit(EXIT_FAILURE);
    }

    // 分块拷贝（只拷贝前半部分）
    char buf[BLOCK_SIZE];
    ssize_t nread;
    off_t remaining = mymessage->mid;
    while (remaining > 0) {
        size_t to_read = (remaining > BLOCK_SIZE) ? BLOCK_SIZE : remaining;
        nread = read(src_fd, buf, to_read);
        if (nread == -1) {
            perror("parent read");
            break;
        }
        if (nread == 0) break;

        if (write(dest_fd, buf, nread) != nread) {
            perror("parent write");
            break;
        }
        remaining -= nread;
    }
    printf("前半部分拷贝完毕！\n");

    // 创建线程
    printf("主线程正在创建分支线程...\n");
    int ret = pthread_create(
        &thread_id,   // 存储线程ID
        NULL,         // 默认属性
        print_message,// 线程函数
        (void *)mymessage // 参数
    );

    if (ret != 0) ERRLOG("创建线程失败");
    
    printf("主线程创建了分支线程 [TID:%lu]\n", thread_id);
    sleep(2);

    // 等待线程结束
    pthread_join(thread_id, NULL);
    
    printf("主线程 [TID:%lu] 结束\n", pthread_self());
    free(mymessage);
    return 0;
}