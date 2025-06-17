#include "LoopDouble.h"

int main(int argc, const char* argv[])
{
    node* H = creat_loop_double();
    insert_tail(H, 1);
    insert_tail(H, 2);
    insert_tail(H, 3);
    insert_tail(H, 4);
    if(!insert_pos(H)) {
    //find_pos(H);
        node* q =delete(H);
        show_no_head(q);
    }
    free_loop_double(H);
    return 0;
}