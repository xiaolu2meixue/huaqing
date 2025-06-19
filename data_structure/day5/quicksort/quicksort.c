#include <stdio.h>
//一次快排需要返回最后基准的位置
int one_sort(int *p,int low,int high)
{
	int base = *(p+low);
	for( ; high>low; )
	{
		//high一侧的数据比基准更大
		for ( ; *(p + high) >= base && high > low; high--);
		*(p + low) = *(p + high);
		for ( ; *(p+low) <= base&&high>low; low++);
		*(p+high) = *(p+low);
	}
	*(p+low) = base;   //将基准放在中间位置
	return low;
}
void sort(int *p,int low,int high)
{
	int ret;
	if(high > low) {  //说明序列中不止一个元素
		ret = one_sort(p, low, high);
		sort(p, low, ret-1);
		sort(p, ret+1, high);
	}
}
int main(int argc, const char *argv[])
{
	int arr[] = {50, 36, 66, 76, 36, 12, 25, 95};
	sort(arr, 0, sizeof(arr)/sizeof(int) - 1);
	for(int i = 0; i < sizeof(arr)/sizeof(int); i++) printf("%d\n", arr[i]);
	return 0;
}