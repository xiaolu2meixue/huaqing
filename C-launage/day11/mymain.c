#include "myheadd.h"

int raws()
{
    int Rows;
    printf("请输入要打印的杨辉三角行数: ");
    scanf("%d", &Rows);
    return Rows;
}
int main(int argc, const char *argv[])
{
    int totalRows = raws();
    my_yanghui(totalRows);
    return 0;
}