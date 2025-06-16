
#include "manager.h"

Class* init(Class* class, int num)
{
    class = (Class*)malloc(sizeof(Class) * num);
    if(class) return class;
    printf("分配失败\n");
    return NULL;
}

void myprint(student student)
{
    printf("student name:%s\n", student.name);
    printf("student id:%d\n", student.id);
    printf("student score:%d\n", student.scores.C_score);

}