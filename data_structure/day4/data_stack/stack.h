#pragma once

#include <myhead.h>
#define MAX 8

typedef struct stack {
    int data[MAX];
    int top;
}stack;

 //1、创建顺序栈                      
 stack* create_stack();              
                                      
 //2、判空                            
 int empty_stack(stack* S);          
                                      
 //3、判满                            
 int full_stack(stack* S);           
                                      
 //4、入栈                            
 void push_stack(stack* S,int value);
                                      
 //5、出栈                            
 int pop_stack(stack* S);            
                                      
 //6、输出栈中元素                    
 void show_stack(stack* S);          
                                      
 //7、销毁栈                          
 void destory(stack* S);             