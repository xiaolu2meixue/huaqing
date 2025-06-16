
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
    printf("学生姓名\t 学号\t\t 年龄\t\t年级\t\t数学\t\tC语言\t\t语文\t\t英语\n");
    printf("%s\t\t %d\t\t %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", student.name, student.id, student.age, student.grade, student.scores.math_score, student.scores.C_score, student.scores.chinese_score, student.scores.english_score);
    // printf("student name:%s\n", student.name);
    // printf("student id:%d\n", student.id);
    // printf("student score:%d\n", student.scores.C_score);

}