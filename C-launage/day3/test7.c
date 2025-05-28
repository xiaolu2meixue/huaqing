#include <stdio.h>

int main() 
{

int num = 0x12345678;

char* result = (*(unsigned char*)&num == 0x12) ? "大端" : "小端";

printf("%s\n", result);

return 0;

}