#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class mystring{
private:
    char* buf;// 指向一个堆空间，该堆空间用来保存外部传入的字符串
    int len; // 记录 buf里面保存的字符串有多少
public:
    mystring(){}
    mystring(const char* r);
    void copy(mystring r);
    bool compare(mystring r);
    void append(mystring r);
    char at(int index);
    void show();
    ~mystring()
    {
        delete[] buf;
    }
};


mystring::mystring(const char* r)
    :len(strlen(r)), buf((char*)calloc(1, len + 1))
{
    strncpy(buf, r, len);
}

void mystring::copy(mystring r)
{
    if (len < r.len) {
        len = r.len;
        free(buf);
        buf = (char*)calloc(1, len + 1);
    }
    strcpy(buf, r.buf);
}

bool mystring::compare(mystring r)
{
    
}

void mystring::append(mystring r)
{
    len = len + r.len;
    char* temp = buf;
    buf = (char*)calloc(1, len + 1);
    strcpy(buf, temp);
    strcat(buf, r.buf);
}

char mystring::at(int index)
{

}

void mystring::show()
{
    cout << buf << endl;
}
int main()
{
    mystring str("hello"); // 这段代码要求一定为mystring类写一个可隐式调用的单参构造函数
    mystring ptr = "world"; // 在写单参构造函数的时候，私有成员len使用列表初始化的形式初始化
    
    str.show();
    ptr.show();

    str.copy(ptr);
    str.show();
    
    // str.append(ptr);
    // str.append("你好");
    
    // str.compare(ptr);
    // str.compare("你好");
    
    // cout << str.at(0) << endl;// 再写一个 at 函数，用来输出 str中第0个字符
}
