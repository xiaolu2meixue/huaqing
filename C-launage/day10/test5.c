#include <myhead.h>
int main(int argc, const char *argv[])
{
	int num1 = atoi(argv[1]);
    int num2 = atoi(argv[3]);
    const char* buf = argv[2];
    switch (*buf) {
	case '+':printf("%d\n",num1+num2);break;
	case '-':printf("%d\n",num1-num2);break;
	case '*':printf("%d\n",num1*num2);break;
	case '/':printf("%d\n",num1/num2);break;
	case '%':printf("%d\n",num1%num2);break;
	default:printf("无此运算\n");
    }
	return 0;
}