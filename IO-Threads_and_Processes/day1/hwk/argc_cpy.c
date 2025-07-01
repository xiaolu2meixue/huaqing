#include <myhead.h>

int main(int argc, char *argv[])
{
    // 检查参数数量
    if (argc != 3) {
        printf("用法: %s <源文件> <目标文件>\n", argv[0]);
        exit(0);
    }
    //打开文件1
    FILE *src_file = fopen(argv[1], "rb");
    if (src_file == NULL) {
        ERRLOG("无法打开源文件");
        exit(0);
    }
    //打开文件2
    FILE *dest_file = fopen(argv[2], "wb");
    if (dest_file == NULL) {
        ERRLOG("无法创建目标文件");
        fclose(src_file);
        exit(0);
    }

    char buffer[4];    //每次拷贝4字节
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, 4, src_file)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dest_file);
        if (bytes_written != bytes_read) {
            ERRLOG("写入文件失败");
            fclose(src_file);
            fclose(dest_file);
            exit(0);
        }
    }

    // 关闭文件流
    fclose(src_file);
    if (fclose(dest_file)) {
        ERRLOG("关闭目标文件失败");
        exit(0);
    }

    printf("文件拷贝成功: %s -> %s\n", argv[1], argv[2]);
    return 0;
}