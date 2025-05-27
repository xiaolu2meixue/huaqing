#include <stdio.h>
#include <string.h>
#define TO_MIN to_min(char)
char to_min(char c) {
	return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}
int main(int argc, const char *argv[])
{
	printf("%c",TO_MIN);
	return 0;
}
