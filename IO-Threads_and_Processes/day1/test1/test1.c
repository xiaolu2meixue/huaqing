#include <myhead.h>

typedef struct Person {
	char name[15];
	int id;
}person;

int main(int argc, const char *argv[])
{

	//打开文件
	FILE* fp = fopen("my.txt", "wb");
	if(!fp) {
		ERRLOG("fopen error");
		return -1;
	}

	//写入文件
	person p = {"Alice", 1};
    size_t written = fwrite(&p, sizeof(person), 1, fp);
    if(written != 1) {
        ERRLOG("fwrite error");
        fclose(fp);
        return -1;
    }

	//关闭写入的文件
	if(EOF == fclose(fp)) {
		ERRLOG("fclose error");
	}

	//读取文件
	fp = fopen("my.txt", "rb");
	person new_p;
	fread(&new_p, sizeof(person), 1, fp);
	printf("Name: %s, ID: %d\n", new_p.name, new_p.id);

	// 关闭读取的文件
    if (fclose(fp) != 0) {
        ERRLOG("fclose error");
        return -1;
    }

	return 0;
}
