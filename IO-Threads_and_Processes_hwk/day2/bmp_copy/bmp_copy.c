#include <myhead.h>

#define BUFFER_SIZE 4096  // 4KB缓冲区

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source.bmp> <destination.bmp>\n", argv[0]);
        return -1;
    }

    const char *src_path = argv[1];
    const char *dst_path = argv[2];
    
    // 打开源文件
    int src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) ERRLOG("Error opening source file");

    // 读取并验证BMP签名
    unsigned char signature[2];
    if (read(src_fd, signature, 2) == -1) {
        close(src_fd);
        ERRLOG("Error reading BMP signature");
    }

    // 读取文件头剩余部分
    unsigned char file_header[12]; // 文件头剩余12字节
    if (read(src_fd, file_header, 12) == -1) {
        close(src_fd);
        ERRLOG("Error reading BMP file header");
    }

    // 提取关键字段
    unsigned int file_size = 
        (file_header[3] << 24) | (file_header[2] << 16) |
        (file_header[1] << 8) | file_header[0];
    
    unsigned int data_offset = 
        (file_header[11] << 24) | (file_header[10] << 16) |
        (file_header[9] << 8) | file_header[8];

    // 读取信息头
    unsigned char info_header[40];
    if (read(src_fd, info_header, 40) == -1) {
        close(src_fd);
        ERRLOG("Error reading BMP info header");
    }

    // 提取关键信息
    // 根据位图信息头提供的信息，info_header是unsigned char类型，所以索引号0~3记录结构所需要的字节、4~7记录宽度、8~11记录长度，然后用按位或整合数据为int类型
    int width = (info_header[7] << 24) | (info_header[6] << 16) | (info_header[5] << 8) | info_header[4];

    int height = (info_header[11] << 24) | (info_header[10] << 16) | (info_header[9] << 8) | info_header[8];
    
    // 打印文件信息
    printf("BMP文件基本信息\n");
    printf("  文件类型: %c%c\n", signature[0], signature[1]);
    printf("  文件大小: %u bytes\n", file_size);
    printf("  偏移量: %u bytes\n", data_offset);
    printf("  文件宽高: %d x %d pixels\n", width, height);

    // 创建目标文件
    int dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        close(src_fd);
        ERRLOG("Error creating destination file");
    }

    // 写入文件头
    if (write(dst_fd, signature, 2) != 2) {
        close(src_fd);
        close(dst_fd);
        ERRLOG("writing signature");
    }
    
    if (write(dst_fd, file_header, 12) != 12) {
        close(src_fd);
        close(dst_fd);
        ERRLOG("Error writing file header");
    }
    
    // 写入信息头
    if (write(dst_fd, info_header, 40) != 40) {
        close(src_fd);
        close(dst_fd);
        ERRLOG("Error writing info header");
    }

    // 计算颜色表大小并复制
    unsigned int color_size = data_offset - 54; // 文件偏移量 - 54 = 14(文件头) + 40(位图信息头)
    if (color_size > 0) {
        unsigned char buffer[BUFFER_SIZE];
        unsigned int remaining = color_size;
        
        for ( ; remaining > 0; ) {
            unsigned int to_read = remaining < BUFFER_SIZE ? remaining : BUFFER_SIZE;
            ssize_t bytes_read = read(src_fd, buffer, to_read);
            
            if (bytes_read <= 0) {
                close(src_fd);
                close(dst_fd);
                ERRLOG("Error reading color table");
            }
            
            ssize_t bytes_written = write(dst_fd, buffer, bytes_read);
            if (bytes_written != bytes_read) {
                close(src_fd);
                close(dst_fd);
                ERRLOG("Error writing color table");
            }
            
            remaining -= bytes_read;
        }
    }

    // 复制像素数据
    // 获取文件总大小
    off_t file_end = lseek(src_fd, 0, SEEK_END);
    if (file_end == (off_t)-1) {
        close(src_fd);
        close(dst_fd);
        ERRLOG("Error seeking to end of file");
    }
    
    // 计算像素数据大小
    off_t pixel_data_size = file_end - data_offset;
    
    // 定位到像素数据开始位置
    if (lseek(src_fd, data_offset, SEEK_SET) == (off_t)-1) {
        close(src_fd);
        close(dst_fd);
        ERRLOG("Error seeking to pixel data");
    }

    // 使用缓冲区复制像素数据
    unsigned char buffer[BUFFER_SIZE];
    off_t remain = pixel_data_size;
    
    for ( ; remain > 0; ) {
        size_t to_read = remain < BUFFER_SIZE ? remain : BUFFER_SIZE;
        ssize_t bytes_read = read(src_fd, buffer, to_read);
        
        if (bytes_read <= 0) {
            if (bytes_read == 0) {
                close(src_fd);
                close(dst_fd);
                fprintf(stderr, "读到文件末尾\n");
            } else {
                close(src_fd);
                close(dst_fd);
                ERRLOG("读像素error");
            }
        }
        
        ssize_t bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            close(src_fd);
            close(dst_fd);
            ERRLOG("写入错误");
        }
        
        remain -= bytes_read;
    }

    // 关闭文件
    if (close(src_fd)) ERRLOG("Error closing source file");
    
    if (close(dst_fd)) ERRLOG("Error closing destination file");

    printf("BMP文件复制成功: %s -> %s\n", src_path, dst_path);
    printf("文件总大小为: %.2f KB\n", file_end / 1024.0);
    
    return -1;
}