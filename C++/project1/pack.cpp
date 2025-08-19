#include "pack.h"

Pack::Pack()
{

}

void Pack::setType(Type type)
{
    this->type = type;
}

void Pack::setBack(Back back)
{
    this->back = back;
}

void Pack::setSize(int size)
{
    pack_size = size;
}

int Pack::size()
{
    return pack_size;
}

Type Pack::getType()
{
    return type;
}

Back Pack::getBack()
{
    return back;
}

void Pack::append(const string &val)
{
    const char* p = val.data();
    short len = strlen(p); // strlen ( char*)
    *(short*)(buf+used) = len;
    used += 2;

    memcpy(buf+used,p,len);
    used += len;

    pack_size = 12 + used;
}

void Pack::append(const char *p, int size)
{
    memset(buf,0,4096);
    memcpy(buf,p,size);
    pack_size = 12 + size;
}

vector<string> Pack::readAll()
{
    vector<string> list;
    int readed_size = 0;// 准备一个记录已读多少自己的数据，方便指针偏移，跳过已读部分
    while(1){
        short size = *(short*)(buf+readed_size);
        if(size == 0){break;}
        readed_size += 2;
        
        char temp[size + 1];
        memset(temp,0,size+1);
        memcpy(temp,buf+readed_size,size);
        readed_size += size;
        
        string str = temp;
        list.push_back(str);
    }
    return list;
}

void Pack::readAll(char* buf,int size){
	// 参数buf需要调用者提前准备一下
	memcpy(buf,this->buf,size);
}

Pack &Pack::operator<<(const string &val)
{
    append(val);
    return *this;
}

void Pack::operator>>(int client)
{
   send(client,(char*)this,pack_size,0);
}



