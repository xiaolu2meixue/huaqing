#include "hash.h"

int main(int argc, const char* argv)
{
    hashlist* list = init_hash();
    put_hash(list, 'A');
    put_hash(list, 'F');
    print_hash(list);
    free(list->data);
    free(list);
    list = NULL;
    return 0;
}   