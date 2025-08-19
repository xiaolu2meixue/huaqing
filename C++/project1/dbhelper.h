#ifndef _dbhelper_h_
#define _dbhelper_h_

#include <sqlite3.h>
#include <iostream>

// 一个数据库刀层负责：打开关闭读取写入一个数据中所有表单的所有操作


class dbHelper{
private:
	sqlite3* db;
	sqlite3_stmt* stmt;
public:
	dbHelper(const std::string& dbname = "");
	~dbHelper();

	// dbHelper 操作的数据库中所有能够操作的表单的函数
	bool regist(const std::string& name,const std::string& pswd);
	bool login(const std::string& name,const std::string& pswd);

	// 写针对别的表单的操作函数
	// 如果说要上设计模式，什么开闭原则之类的，也在这里派生就行了
	// 总而言之，数据库刀层目的很简单：将针对数据库的所有操作，集中在一起，方便查询修改
};



#endif
