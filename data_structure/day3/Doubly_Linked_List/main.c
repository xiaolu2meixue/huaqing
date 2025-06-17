#include "double.h"

int main(int argc, const char* argv[])
{
    node* H = creat_double();
    insert_tail(H, 1);
    insert_tail(H, 2);
    insert_tail(H, 3);
    insert_tail(H, 4);
    //delete_pos(H);
    //find_pos(H);
    show(H);
    free_double(H);
    return 0;
}