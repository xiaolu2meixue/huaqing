#ifndef PACK_H
#define PACK_H

#include <cstring>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>


enum Type{
    TYPE_REGIST,
    TYPE_LOGIN,
    TYPE_FILE_UPLOAD_REQUEST,
    TYPE_FILE_UPLOADING,
    TYPE_FILE_UPLOAD_END
};

// 协议包发给服务器之后，服务器要处理，如果处理成功，服务器发给客户端的协议包里面的Back，就是SUCCESS
enum Back{
    BACK_SUCCESS,
    BACK_ERR
};

using std::string;
using std::vector;

class Pack
{
	
private:
    int pack_size = 12;// 记录整个协议包大小，方便服务器知道当前发过去的协议包有多大
    Type type;
    Back back;
    char buf[4096] = "";
    int used = 0;
public:
    Pack();
    void append(const string& val);// 将外部的字符串数据，写入协议包的buf里面
	void append(const char* p,int size);
    vector<string> readAll();// 读取协议包的buf所有字符串
	void readAll(char* buf,int size);
    Pack& operator<<(const string& val);
    void operator>>(int client);
    
    void setType(Type type);
    void setBack(Back back);
    void setSize(int size);

    int size(); // pack_size的get接口
    Type getType();
    Back getBack();
};

#endif // PACK_H

