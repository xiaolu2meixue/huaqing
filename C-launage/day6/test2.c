#include <myhead.h>
int Str(char* str)
{
	char ch;
	for (int count = 0; ;count++)
	{
		printf("请输入：（输入#结束输入）");
		scanf(" %c", &ch);
		if (ch == '#') return count;
		str[count] = ch;
	}
    return 0;
}
void print()
{
	char STR[100];
	int COUNT= Str(STR);
	for (int i = 0; i < COUNT; i++)
	{
		printf("%c", STR[i]);
	}
	
}
int main(int argc, const char *argv[])
{
	
	print();
	return 0;
}
