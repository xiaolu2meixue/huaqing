#include "hash.h"

hashlist* init_hash()
{
    hashlist* list = (hashlist*)malloc(sizeof(hashlist));
    list->num = 0;
    list->data = (char*)malloc(sizeof(char) * NUM);
    for (int i = 0; i < NUM; i++) {
        list->data[i] = 0;
    }
    return list;
}

int hash(int data)
{
    return data % NUM;
}

void put_hash(hashlist* list, char data)
{
    int index = hash(data);
    if (list->data[index] != 0) {
        int count = 1;
        for ( ; list->data[index] != 0; ) {
            index = hash(hash(data) + count);
            count++;
        }
    }
    list->data[index] = data;
    list->num++;
}

void print_hash(hashlist* list)
{
    for (int i = 0 ; i < list->num; i++) printf("%c\n",list->data[i]);
} 