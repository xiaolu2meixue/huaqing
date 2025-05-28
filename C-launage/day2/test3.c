#include <stdio.h>
#include <string.h>
#define TO_MIN(x) to_min((char)(x))
char to_min(char c) 
{
	return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}
int main(int argc, const char *argv[])
{
	char x =to_min('c');
	printf("%c",to_min(x));
	return 0;
}
