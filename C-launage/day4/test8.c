#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int maxmin(int a ,int b)
{
	if (a > b) return b;
    else return a;
}
int maxapp(int a, int b)
{
    int num = maxmin(a ,b);
    while(num > 0){
        if (a%num == 0 && b%num == 0) return num;
        num--;
    }
}
	
int main(int argc, const char *argv[])
{
    int A, B, NUM;
    scanf("%d %d", &A, &B);
    NUM = maxapp(A, B);
    printf("最大公约数为：%d\n", NUM);
	return 0;
}
