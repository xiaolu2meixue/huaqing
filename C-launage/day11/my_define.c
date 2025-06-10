#include <myhead.h>
#define MAX(a, b)({\
	int max;\
	if (a > b) max = a;\
	else max = b;\
	max;\
})
#define MIN(a, b) do\
{\
	if (a < b) printf("最小值为：%d\n", a);\
	else printf("最小值为：%d\n", b);\
} while (0);
int main(int argc, const char *argv[])
{
	int x, y;
	scanf("%d %d", &x, &y);
	printf("最大值为：%d\n",MAX(x, y));
	MIN(x, y);
	return 0;
}
