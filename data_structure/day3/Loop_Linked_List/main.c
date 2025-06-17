#include "loop.h"

int main(int argc, const char* argv[])
{
    node* H = creat_loop();
    insert_tail(H, 1);
    insert_tail(H, 2);
    insert_tail(H, 3);
    insert_tail(H, 4);
    node* q = delete(H);
    show_no_head(q);
    // delete_pos(H);
    //show_loop(H);
    free(H);
    H = NULL;
    return 0;
}