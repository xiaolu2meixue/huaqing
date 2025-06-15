#include "common.h"
#include "manager.h"

extern int main_menu();
extern int log_on(const char* passwd, int id);

student* allstudent = NULL;
extern Class* class;

int main(int argc, const char* argv[])
{
    class = init(class, 10);
    if(log_on(INITIAL_PASSWORD, 000001) == 1) return -1;
    for(; ; main_menu());


    return 0;
}