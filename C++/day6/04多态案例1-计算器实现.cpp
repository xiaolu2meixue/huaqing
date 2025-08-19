#include <iostream>
#include <string>

using namespace std;

//普通写法
class Calculatar
{
public:
    int getResult(string oper)
    {
        if (oper == "+")
        {
            return m_Num1 + m_Num2;
        }
        else if (oper == "-")
        {
            return m_Num1 - m_Num2;
        }
        else if (oper == "*")
        {
            return m_Num1 * m_Num2;
        }
        //如果需要扩展功能，需要修改源码
        //在真实开发中提倡开闭原则：即对扩展进行开发，对修改进行关闭
        return 0;
    }
    int m_Num1;
    int m_Num2;
};

void test01()
{
    Calculatar c;
    c.m_Num1 = 10;
    c.m_Num2 = 10;
    cout << "m_Num1 + m_Num2 = " << c.getResult("+") << endl;
    cout << "m_Num1 - m_Num2 = " << c.getResult("-") << endl;
    cout << "m_Num1 * m_Num2 = " << c.getResult("*") << endl;
}

/*
**********************************************************
*/

//利用多态实现计算器

//实现计算器抽象类
class AbstractCalculatar
{
public:
    virtual int getResult()
    {
        return 0;
    }
    int m_Num1;
    int m_Num2;
};

//加法计算器类
class AddCalculatar :public AbstractCalculatar
{
public:
    int getResult()
    {
        return m_Num1 + m_Num2;
    }
};

//减法计算器类
class SubCalculatar :public AbstractCalculatar
{
public:
    int getResult()
    {
        return m_Num1 - m_Num2;
    }
};

//乘法计算器类
class MulCalculatar :public AbstractCalculatar
{
public:
    int getResult()
    {
        return m_Num1 * m_Num2;
    }
};

void test02()
{
    //多态使用条件
    //父类指针或者引用指向子类对象

    //加法运算
    AbstractCalculatar* abc = new AddCalculatar;
    
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;

    cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->getResult() << endl;
    //用完后记得销毁
    delete abc;

    //减法运算
    abc = new SubCalculatar;
    abc->m_Num1 = 100;
    abc->m_Num2 = 100;
    cout << abc->m_Num1 << " - " << abc->m_Num2 << " = " << abc->getResult() << endl;
    delete abc;

    //乘法运算
    abc = new MulCalculatar;
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;
    cout << abc->m_Num1 << " * " << abc->m_Num2 << " = " << abc->getResult() << endl;
    delete abc;

}

int main(int argc, const char** argv)
{
    test02();
    return 0;
}
