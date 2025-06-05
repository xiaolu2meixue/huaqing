#include <myhead.h>
int i = 0;
int dif_value(const char* buffer1, const char* buffer2, int min_len, int max_len)
{
    // 终止条件1：找到不同字符
    if (buffer1[i] != buffer2[i]) {
        return buffer1[i] - buffer2[i];
    }
    
    // 终止条件2：比较完公共部分
    if (i == min_len) {
        if (min_len == max_len) return 0;
        return buffer1[min_len] - buffer2[min_len];
    }
    
    // 递归步骤：移动到下一个字符
    i++;
    dif_value(buffer1, buffer2, min_len, max_len);
}

int main(int argc, const char *argv[])
{
    int len;
    char buf1[128] = { 0 };
    char buf2[128] = { 0 };
    fgets(buf1, 128, stdin);
    buf1[strcspn(buf1, "\n")] = '\0';
    fgets(buf2, 128, stdin);
    buf2[strcspn(buf2, "\n")] = '\0';
    int len1 = strlen(buf1);
    int len2 = strlen(buf2);
    int min_len = (len1 < len2) ? len1 : len2;
    int max_len = (len1 > len2) ? len1 : len2;
    
    int dif = dif_value(buf1, buf2, min_len, max_len);
    printf("%d\n", dif);
    return 0;
}