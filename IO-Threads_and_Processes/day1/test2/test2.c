#include <myhead.h>

int main(int argc, const char *argv[])
{
	//打开文件
	FILE* fp = fopen("my.txt", "w+");
	if(!fp) {
		ERRLOG("fopen error");
		return -1;
	}
	// printf("fopen sucess..\n");

	//写入文件
	if(EOF == fputc('a', fp)) {
		printf("fputc error..\n");
		return -1;
	}
	
	//计算文件大小
	long len = ftell(fp); printf("length of file: %ld\n",len);


	//移动光标
	//if (EOF == fseek(fp, 0, SEEK_SET)) ERRLOG("fseek error");
	rewind(fp);

	//读取文件
	char buf = fgetc(fp);
	if (EOF == buf) {
		ERRLOG("fgetc error");
		return -1;
	}
    printf("buf = %c\n", buf);

	//关闭文件
	if(EOF == fclose(fp)) {
		ERRLOG("fclose error");
	}

	return 0;
}
