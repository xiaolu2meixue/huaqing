#include "stack.h"
int main(int argc, const char* argv)
{
    stack* S = create_stack();
    push_stack(S, 1);
    pop_stack(S);
    push_stack(S, 2);
    push_stack(S, 3);
    push_stack(S, 4);
    show_stack(S);
    destory(S);
    return 0;
}