#ifndef _COMMON_H_
#define _COMMON_H_

#include <myhead.h>
#define MAX 60
#define INITIAL_PASSWORD     "123456"
#define INITIAL_id            000001

enum grade {
    First = 1,
    Second,
    Third
};

typedef struct Score {
    int math_score;
    int C_score;
    int chinese_score;
    int english_score;
}score;

typedef struct Student {
    int id;
    char name[10];
    char passwd[10];
    int age;
    int myclass;    //班级
    int grade;      //年级
    score scores;
}student;

typedef struct Class {
    int num;     //班级号
    student c_student[MAX];
    int grade;    //年级，索引
    int member;   //具体人数
}Class;

typedef struct Teacher {
    int id;
    char name[10];
    Class* T_class;
}Teacher;

// typedef struct classmanager {

// };

#endif // _COMMON_H_