#include <iostream>
#include <cstring>

class mystring {
private:
    char* buf;  // 指向堆空间，用于存储字符串
    int len;    // 记录字符串长度（不含结尾空字符）

public:
    // 单参构造函数（支持隐式转换），使用初始化列表初始化 len
    mystring(const char* s = nullptr) : len(s ? strlen(s) : 0) {
        buf = new char[len + 1];  // 分配空间（包含结尾空字符）
        if (s) strcpy(buf, s);    // 复制有效字符串
        else buf[0] = '\0';       // 处理空指针
    }

    // 析构函数：释放堆内存
    ~mystring() {
        delete[] buf;
    }

    // 深拷贝构造函数
    mystring(const mystring& other) : len(other.len) {
        buf = new char[len + 1];
        strcpy(buf, other.buf);
    }

    // 赋值运算符重载
    mystring& operator=(const mystring& other) {
        if (this != &other) {
            delete[] buf;          // 释放原有内存
            len = other.len;
            buf = new char[len + 1];
            strcpy(buf, other.buf);
        }
        return *this;
    }

    // 复制函数（mystring 版本）
    void copy(const mystring& s) {
        *this = s;  // 重用赋值运算符
    }

    // 复制函数（C 字符串版本）
    void copy(const char* s) {
        delete[] buf;                // 释放旧内存
        len = s ? strlen(s) : 0;     // 计算新长度
        buf = new char[len + 1];     // 分配新内存
        if (s) strcpy(buf, s);
        else buf[0] = '\0';
    }

    // 追加函数（mystring 版本）
    void append(const mystring& s) {
        append(s.buf);  // 重用 C 字符串版本
    }

    // 追加函数（C 字符串版本）
    void append(const char* s) {
        if (!s || *s == '\0') return;  // 忽略空字符串
        
        int s_len = strlen(s);
        char* new_buf = new char[len + s_len + 1];  // 新空间
        
        strcpy(new_buf, buf);       // 复制原内容
        strcat(new_buf, s);          // 追加新内容
        
        delete[] buf;               // 释放旧内存
        buf = new_buf;              // 指向新内存
        len += s_len;               // 更新长度
    }

    // 比较函数（mystring 版本）
    int compare(const mystring& s) const {
        return strcmp(buf, s.buf);  // 直接比较缓冲区
    }

    // 比较函数（C 字符串版本）
    int compare(const char* s) const {
        return s ? strcmp(buf, s) : (buf[0] ? 1 : 0);  // 处理空指针
    }

    // 显示字符串内容
    void show() const {
        std::cout << buf;
    }

    // 获取指定位置字符（带边界检查）
    char at(int index) const {
        return (index >= 0 && index < len) ? buf[index] : '\0';
    }
};