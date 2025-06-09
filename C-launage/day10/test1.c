#include <myhead.h>
int main(int argc, const char *argv[])
{
	char* p = (char*)malloc(sizeof(char) * 10);
	strcpy(p,"hello");
	*(p + 1) = 'E';
	puts(p);
	free(p);
	p = NULL;
	return 0;
}
