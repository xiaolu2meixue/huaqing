#include <myhead.h>
int Arr(int* arr)
{
	int num;
	for (int count = 0; ;count++)
	{
		printf("请输入：（输入-1结束输入）");
		scanf("%d", &num);
		if (num == -1) return count;
		arr[count] = num;
	}
    return 0;
}
void shengxu()
{
	int ARR[100];
	int len = Arr(ARR);
	int min;
	for (int i = 0; i < len; i++)
	{
		min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (ARR[min] > ARR[j]) min = j;
			
		}
		int t = ARR[i]; ARR[i] = ARR[min]; ARR[min] = t;
	}
	for (int i = 0; i < len; i++)
	{
		printf("%d\t",ARR[i]);
	}
	printf("\n");
	
}
int main(int argc, const char *argv[])
{
	shengxu();
	return 0;
}
