#include <iostream>
#include <string>
#include <set>

using namespace std;

class Stu
{
private:
    int score;
    string name;

public:
    Stu(const string& name = "",int score = 0)
    :name(name),score(score)
    {
    }

    bool operator<(const Stu& r)const{
        return this->name < r.name;
    }

    void show()const{
        //this->name = "无名";
    }

    // Stu* const
    void setScore(int score){
        cout << "无const" << endl;
        this->score = score;
    }

    void setScore(int score)const{
        // 此处的this指针类型为 const Stu* const
        cout << "const" << endl;
        (const_cast<Stu*>(const_cast<const Stu*>(this)))->setScore(score);
    }

    string getName()const{
        return name;
    }

    int getScore()const{
        return score;
    }
};

int main(int argc,const char** argv){
    set<Stu> s;

    /*
    for(auto ele : s){
        // 这里的每一个 ele 都是 const Stu 类型的
        ele.show(); // 调用每一个Stu元素的show函数
    }
    */

    Stu zs("张三",100);
    s.insert(zs);

    s.insert(Stu("李四",110));

    s.insert({"王五",90});

    s.insert({"赵六",90});

    s.insert({"张三",150});

    set<Stu>::iterator tar = s.find({"张三",0});
    //cout << tar->getName() << endl;
    tar->setScore(110);

    for(auto ele : s){
        cout << ele.getName() << endl;
        cout << ele.getScore() << endl;
        cout << "================" << endl;
    }

    return 0;
}