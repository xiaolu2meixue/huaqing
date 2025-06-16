#include "link.h"

int main(int argc, const char* argv[])
{
    node* H = creat_link();
    insert_head(H, 1);
    insert_head(H, 2);
    insert_head(H, 3);
    insert_head(H, 4);
    invert_link2(H);
    show_link(H);
    return 0;
}