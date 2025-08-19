#include <iostream>
#include <string>

class MyPrint
{
public:
	void operator()(std::string test)
	{
		std::cout << test << std::endl;
	}

private:

};
class MyAdd
{
public:
	int operator()(int a, int b, int c)
	{
		return a + b + c;
	}
};

void test01()
{
	MyPrint myprint;
	myprint("hello world!");
}

void test02()
{
	MyAdd myadd;
	std::cout << MyAdd()(10, 10 ,10) << std::endl;
	std::cout << myadd(10, 10, 10) << std::endl;
}

int main()
{
	test01();
	test02();
	return 0;
}