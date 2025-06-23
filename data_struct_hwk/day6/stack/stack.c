#include <myhead.h>

int main(int argc, const char *argv[])
{
	char str[128];
	char str_find[128];
	int top = -1;
	int i;
	fgets(str, 128, stdin);
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] == '(' || str[i] == '[' || str[i] == '{') str_find[++top] = str[i];
		if (str[i] == ')' || str[i] == ']' || str[i] == '}') {
			if (str[i] == ')' && str_find[top] == '(' || str[i] == ']' && str_find[top] == '[' || str[i] == '}' && str_find[top] == '{') --top;
			else break;
		}
	}
	if(str[i]!=0 || top != -1) printf("匹配失败\n");
	else printf("匹配成功\n");
	return 0;
}
