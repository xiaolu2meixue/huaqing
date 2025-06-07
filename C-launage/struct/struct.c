//typedef 关键字

#include <myhead.h>
enum SEX {
    WOMAN,
    MAN,
};

typedef struct shoe{
    char name[10];
    int type;
}shoe;

typedef struct people {
    int age;  //4 
    char name[13];  //13   16
    int height;
    int high;
    int SEX;  //1为男
    int* buf;
    shoe* shoes;
}pl, *PL;

// int mystruct(struct people xxx)
// {

// }

int main(int argc, const char* argv[])
{
    //直接赋值
    struct people zf = {23, "zongfei", 110, 172, 1};
    printf("age = %d, name = %s", zf.age, zf.name);

    //最常用的
    struct people xzl = {
        .height = 178,
        .name = "xuanzhonglu"
    };

    struct people zs;
    zs.age = 19;

    printf("sssssss   %ld\n", sizeof(pl));

    PL lisi = (struct people*)malloc(sizeof(pl));

    lisi->age = 99;
    lisi->buf = (int*)malloc(40);
    //lisi->shoes.name = "sss";  错，不能这么写
    strcpy(lisi->shoes->name, "ssss");

    return 0;
}