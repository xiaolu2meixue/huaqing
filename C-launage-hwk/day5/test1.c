#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int Hundred()
{
	int x, y;
	for ( x = 0; x <= 100; x++){
		for (y = 100; y >= 0; y--){
		
		if (((15 * x) + (9 * y) + (100-(x + y))) == 300){
			printf("\t 鸡翁：%d\t鸡母： %d\t 鸡雏：%d\n", x , y, 100-(x + y));
			continue;
			}
		}
		
	}
	
}
int main(int argc, const char *argv[])
{
	Hundred();
	return 0;
}
