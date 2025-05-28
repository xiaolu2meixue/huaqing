#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//返回值 名称 参数（形参）
// 返回值：数据类型，int char long short struct(必须是个确切的结构体) 指针
// 名称：自己定义的一个不重名的 MinToMax minToMax min_to_max
// 参数：可以有多个(数据类型)

int mintomax(char* buf, int myint);  //只是声明，还没定义
int ret_int(int a)
{
    return a + 10;
}

int main()
{
    int ret;
    int mybuf = ret_int(0);
    char buffff[] = "ssssssss";
    ret = mintomax(buffff, rer_int(mybuf));
    if(!ret){
        
    }
    return 0;
}

int mintomax(char* buf, int myint)
{
    int a = 10;
    myint -= a; //myint = myint - a
    printf("zongfei %s", buf);
    printf("zongfei %d", myint);
    if(myint < 10) return myint;

    return 0;
}


// int buf[10] = { 101010, 6547568, 3, 4, 5, 6, 7 ,0, 13, 99};
// buf[0] == 1;
// buf[1] == 2; 

// int* buf1 = NULL;
// char* buf2 = NULL;