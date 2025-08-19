#include <iostream>

using namespace std;

//多态案例2 制作饮品
class AbstractDrinking
{
public:
    //煮水
    virtual void Boil() = 0;

    //冲泡
    virtual void Brew() = 0;

    //倒入杯中
    virtual void PourInCup() = 0;

    //加入辅料
    virtual void PutSomething() = 0;

    //制作饮品
    virtual void MakeDrink()
    {
        Boil();
        Brew();
        PourInCup();
        PutSomething();
    }
};

//制作咖啡
class Coffee :public AbstractDrinking
{
public:
    virtual void Boil()
    {
        cout << "煮农夫山泉" << endl;
    }
    virtual void Brew()
    {
        cout << "冲泡咖啡" << endl;
    }
    virtual void PourInCup()
    {
        cout << "倒入马克杯中" << endl;
    }
    virtual void PutSomething()
    {
        cout << "加入牛奶和焦糖" << endl;
    }
};

//制作茶叶
class Tea :public AbstractDrinking
{
public:
    virtual void Boil()
    {
        cout << "煮农夫山泉" << endl;
    }
    virtual void Brew()
    {
        cout << "冲泡茶叶" << endl;
    }
    virtual void PourInCup()
    {
        cout << "倒入玻璃杯中" << endl;
    }
    virtual void PutSomething()
    {
        cout << "加入人参和枸杞" << endl;
    }
};

void doWork(AbstractDrinking* abs)
{
    abs->MakeDrink();
    delete abs;
}

void test01()
{
    //制作咖啡
    doWork(new Coffee);

    cout << "-----------------" << endl;
    //制作茶叶              
    doWork(new Tea);
}

int main()
{
    test01();
    return 0;
}
