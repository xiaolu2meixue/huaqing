#include <myhead.h>

int main(int argc, char *argv[])
{
    // 检查参数数量
    if (argc != 2) {
        printf("用法: %s <源文件>\n", argv[0]);
        exit(0);
    }
    //打开文件1
    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        ERRLOG("无法打开源文件");
        exit(0);
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    printf("文件大小为：%ld\n", file_size);
    return 0;
}