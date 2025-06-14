#include "seq.h"


int main()
{
    int data[6];
    scanf("%d %d %d %d %d %d",&data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);

    seq* S = creat_seq(S);
    for(int i = 0; i < 6 ;i++) insert_end(data[i], S);

    delete_end(S);
    delete_start(S);

    for(int i = 0; i < S->len ;i++) printf("seq[%d] = %d\n", i, S->arr[i]);
    
    free(S->arr);
    free(S);
    
    return 0;
}