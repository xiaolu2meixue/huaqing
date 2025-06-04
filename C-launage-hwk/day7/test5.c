#include <myhead.h>
int Str(char* str)
{
	printf("请输入字符串：");
	gets(str);
	int len = strlen(str);
    return len;
}
int rever(char* buf)
{
    int LEN = Str(buf);
    for (int i = 0; i < LEN/2; i++) 
    {
        int temp1 = buf[i];
        buf[i] = buf[LEN - 1 - i];
        buf[LEN -1 - i] = temp1;
    }
    return LEN;
}
int word_rever(char* buffer)
{
    int Len = rever(buffer);
    int start = 0;
     for (int i = 0; i <= Len; i++)
    {
        if (buffer[i] == ' ' || buffer[i] == '\0') {
            for (int p = start ,q = i - 1; p < q; p++, q--)
            {
                char temp2 = buffer[p];
                buffer[p] = buffer[q];
                buffer[q] = temp2;
            }
            start = i + 1;
        }
    }
    
}
int main(int argc, const char *argv[])
{
    char BUFFER[100] = {};
    word_rever(BUFFER);
    puts (BUFFER);
    return 0;
}