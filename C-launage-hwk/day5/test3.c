#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int is_runnian(int year)
{
	if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return 1;
	else return 0;
}
int total(int year, int month, int day, int* total_days)
{
	int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31 ,31 ,30, 31, 30, 31};
	*total_days = 0;
	if (is_runnian(year)) {
        days_in_month[2] = 29;
    }
	for (int i = 1; i < month; i++) {
        *total_days += days_in_month[i];
    }
	*total_days += day;
}
int main(int argc, const char *argv[])
{
	int year, month, day, Total_days;
	printf("请输入年份：");
    scanf("%d", &year);
    printf("请输入月份：");
    scanf("%d", &month);
    printf("请输入日期：");
    scanf("%d", &day);
	total(year, month, day, &Total_days);
	printf("%d年 %d月 %d日,是一年中第%d天",year, month, day, Total_days);
	return 0;
}
