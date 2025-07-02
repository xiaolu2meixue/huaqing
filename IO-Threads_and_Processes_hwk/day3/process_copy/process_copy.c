#include <myhead.h>

#define BLOCK_SIZE 4096 // 分块大小

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *src_path = argv[1];
    const char *dest_path = argv[2];

    // 打开源文件
    int src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) {
        perror("open source");
        exit(EXIT_FAILURE);
    }

    // 获取文件大小
    off_t file_size = lseek(src_fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("lseek");
        close(src_fd);
        exit(EXIT_FAILURE);
    }
    
    // 计算中点位置
    off_t mid = file_size / 2;
    
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

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // 子进程：拷贝后半部分
        // 子进程重新打开文件
        int child_src_fd = open(src_path, O_RDONLY);
        int child_dest_fd = open(dest_path, O_WRONLY);
        if (child_src_fd == -1 || child_dest_fd == -1) {
            perror("child open");
            exit(EXIT_FAILURE);
        }

        // 定位到中点位置
        if (lseek(child_src_fd, mid, SEEK_SET) == -1 || 
            lseek(child_dest_fd, mid, SEEK_SET) == -1) {
            perror("child lseek");
            exit(EXIT_FAILURE);
        }

        // 分块拷贝
        char buf[BLOCK_SIZE];
        ssize_t nread;
        while ((nread = read(child_src_fd, buf, BLOCK_SIZE))) {
            if (nread == -1) {
                perror("child read");
                break;
            }
            if (nread == 0) break; // EOF

            if (write(child_dest_fd, buf, nread) != nread) {
                perror("child write");
                break;
            }
        }

        close(child_src_fd);
        close(child_dest_fd);
        exit(EXIT_SUCCESS);

    } else { // 父进程：拷贝前半部分
        // 定位到文件开头
        if (lseek(src_fd, 0, SEEK_SET) == -1 || 
            lseek(dest_fd, 0, SEEK_SET) == -1) {
            perror("parent lseek");
            exit(EXIT_FAILURE);
        }

        // 分块拷贝（只拷贝前半部分）
        char buf[BLOCK_SIZE];
        ssize_t nread;
        off_t remaining = mid;
        while (remaining > 0) {
            size_t to_read = (remaining > BLOCK_SIZE) ? BLOCK_SIZE : remaining;
            nread = read(src_fd, buf, to_read);
            if (nread == -1) {
                perror("parent read");
                break;
            }
            if (nread == 0) break; // 不应该提前结束

            if (write(dest_fd, buf, nread) != nread) {
                perror("parent write");
                break;
            }
            remaining -= nread;
        }

        close(src_fd);
        close(dest_fd);

        // 等待子进程结束
        waitpid(pid, NULL, 0);
        printf("File copied successfully!\n");
        exit(EXIT_SUCCESS);
    }
}