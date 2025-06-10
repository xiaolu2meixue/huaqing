#include <myhead.h>
char* my_strcat()
{
	char* str = (char*)malloc(sizeof(char) * 40);
	char str1[20] = "hello";
	char str2[20] = "world";
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char* i = str1 + len1;
	char* j = str2;
    for (; j <= str2 + len2;i++, j++) *i = *j;
	strcpy(str, str1);
	return str;
}
int main(int argc, const char *argv[])
{
	char* mystr = my_strcat();
	fputs(mystr, stdout);
	free(mystr);
	mystr = NULL;
	return 0;
}
