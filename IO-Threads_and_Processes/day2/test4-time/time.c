#include <myhead.h>
int main(int argc, const char *argv[])
{
	time_t t;
	t = time(&t);
	struct tm* s = localtime(&t);
	printf("时间：%02d-%02d-%02d-%02d:%02d:%02d", s->tm_year + 1900, s->tm_mon + 1, s->tm_mday, s->tm_hour + 1, s->tm_min + 1, s->tm_sec);
	return 0;
}
