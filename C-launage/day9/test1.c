#include <myhead.h>
int main(int argc, const char *argv[])
{
	int a = 0x12345678;
	char* p = (char*) a;
	printf("%d", *p);
	return 0;
}
