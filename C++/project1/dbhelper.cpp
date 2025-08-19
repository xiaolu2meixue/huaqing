#include "dbhelper.h"

using std::string;

dbHelper::dbHelper(const string& dbname){
	sqlite3_open(dbname.data(),&db);
}

dbHelper::~dbHelper(){
	sqlite3_close(db);
}

bool dbHelper::regist(const string& name,const string& pswd){
	sqlite3_prepare_v2(db,"insert into user(name,pswd) values(?,?)",-1,&stmt,nullptr);
	sqlite3_bind_text(stmt,1,name.data(),-1,nullptr);
	sqlite3_bind_text(stmt,2,pswd.data(),-1,nullptr);
	int res = sqlite3_step(stmt);
	if(res != SQLITE_ROW && res != SQLITE_DONE){
		return false;
	}
	return true;
}


bool dbHelper::login(const string& name,const string& pswd){
	sqlite3_prepare_v2(db,"select pswd from user where name = ?",-1,&stmt,nullptr);
	sqlite3_bind_text(stmt,1,name.data(),-1,nullptr);
	int res = sqlite3_step(stmt);
	if(res == SQLITE_DONE){
		return false;
	}else if(res == SQLITE_ROW){
		string db_pswd = (const char*)sqlite3_column_text(stmt,0);
		if(pswd == db_pswd){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}
