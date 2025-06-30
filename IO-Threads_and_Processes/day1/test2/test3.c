#include <myhead.h>

int main(int argc, const char *argv[])
{
	//打开文件
	FILE* fp = fopen("my.txt", "r+");
	if(!fp) {
		ERRLOG("fopen error");
		return -1;
	}

	//写入文件
	char buf[128] = "";
	for (int i = 0; i < 5; i++)
	{
		printf("请输入buf:");
		fgets(buf, 128, stdin);
		if (EOF == fputs(buf, fp)) {
		printf("fputs error");
		return -1;
		}
	}
	
	//计算文件大小

	//移动光标
	rewind(fp);
	for( ; ; ) {
		//读取文件
		memset(buf, 0, sizeof(buf));
		if (NULL == fgets(buf, sizeof(buf), fp)) {
			printf("读取到文件结尾或失败\n");
			break;
		}
		buf[strcspn(buf, "\n")] = '\0';
		printf("buf = [%s]\n", buf);
	}
	
	//关闭文件
	if(EOF == fclose(fp)) {
		ERRLOG("fclose error");
	}

	return 0;
}
