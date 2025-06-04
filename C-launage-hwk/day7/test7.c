#include <myhead.h>
int main(int argc, const char *argv[])
{
    int i;
    char str[][10] = {};
	for ( i = 0; i < 5; i++)
    {
        printf("请输入姓名：");
        puts(str[i]);
    }
    for (int j = 0; j < 5; j++)
    {
        for (int q = j; q < j + 5 - 1; q++)
        {
            if (strcmp(str[q], str[q + 1]) > 0)
            {
                char temp;
                strcpy(temp, str[q]);
                strcpy(str[q], str[q + 1]);
                strcpy(str[q + 1], temp);
            }
            
        }
        
    }
    
    
	return 0;
}
