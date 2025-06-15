#ifndef _MANAGER_H_
#define _MANAGER_H_


#include "common.h"

typedef void (*MYPRINTF)(student);
void myprint(student student);
Class* init(Class* class, int num);

#endif // _MANAGER_H_