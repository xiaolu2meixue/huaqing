#include <myhead.h>
int sum;
void fun(int m)
{
	sum += m;
	if(m == 0) {
		printf("%d\n",sum);
		return;
	}
	else fun(m-1);
}
int main(int argc, const char *argv[])
{
	int n;
	printf("请输入n:");
	scanf("%d", &n);
	fun(n);
	return 0;
}
