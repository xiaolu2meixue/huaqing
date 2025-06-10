#include <myhead.h>
char* my_strcat()
{
	char* str1 = (char*)malloc(sizeof(char) * 40);
	str1 = "hello";
	char str2[20] = "world";
    int i;
    for (i = 0; (str1 + i) != 0; i++);
    for (int j = 0; *(str2 + j) != 0; i++, j++) str1[i] = str2[j];
	return str1;
}
int main(int argc, const char *argv[])
{
	char* mystr = my_strcat();
	fputs(mystr, stdout);
	free(mystr);
	mystr = NULL;
	return 0;
}
