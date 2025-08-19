#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <iostream>
#include <map>


#include "pack.h"
#include "dbhelper.h"


using namespace std;




bool client_handler(int client,dbHelper& db);

struct User{
	string username;
	FILE* fp;
	// 处理分包时需要以下3个数据
	Pack readed_pack; // 用来暂存已经读取到的部分协议包 以及 用来拼接未读取的协议包
	int readed_pack_size = 0; // 用来记录已读协议包的大小
	int unreaded_pack_size = 0; // 用来记录未读协议包的大小

	 // 处理4个字节的size 发生分包的可能性
	int readed_size = 0;
	int readed_size_size = 0;
	int unreaded_size_size = 0;
};

template <class T1,class T2>
class mymap:public map<T1,T2>{
public:
	int operator[](const string& name){
		for(auto ele:*this){
			if(ele.second.username == name){
				return ele.first;
			}
		}
		return -1;
	}

	T2& operator[](const T1& key){
		return this->map<T1,T2>::operator[](key);
	}
};

mymap<int,User> m;// 键为：客户端套接字，值为 User 对象
// 这个map的作用为：存储所有在线用户的套接字信息和用户的相关信息



int main(int argc, const char *argv[])
{
	if(argc < 2){
		printf("请输入端口号\n");
		return 1;
	}

	dbHelper db("user.db");

	short port = atoi(argv[1]);
	// "abc123" -> 0
	int server = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;	
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");

	if(bind(server,(struct sockaddr*)&addr,sizeof(addr)) == -1){
		perror("bind");
		return 1;
	}

	listen(server,10);

	// 创建epoll监视列表
	int epfd = epoll_create1(EPOLL_CLOEXEC);

	// 将 0 和 server 添加进入监视列表
	//struct epoll_event epoll_stdin = {.events = EPOLLIN ,data:{fd:server}};
	struct epoll_event epoll_stdin = {events : EPOLLIN , data:{fd:0}};
	struct epoll_event epoll_server = {events : EPOLLIN , data:{fd : server}};

	epoll_ctl(epfd,EPOLL_CTL_ADD,0,&epoll_stdin);
	epoll_ctl(epfd,EPOLL_CTL_ADD,server,&epoll_server);
	int eplen = 2;


	while(1){
		// 提前准备一个激活列表
		struct epoll_event list[20] = {0};
		int count = epoll_wait(epfd,list,eplen,-1);

		for(int i=0;i<count;i++){
			// list里面全都是激活的描述符，最多判断一下 ，以何种方式激活的

			// 将激活的具体描述符单独取出
			int fd = list[i].data.fd;
			if(fd == 0){
				char buf[1024] = "";
				scanf("%s",buf);
				getchar();
				printf("键盘输入数据:%s\n",buf);
				continue;
			}

			if(fd == server){
				printf("有客户端连接\n");
				struct sockaddr_in client_addr = {0};
				socklen_t client_len = sizeof(client_addr);
				int client = accept(server,(struct sockaddr*)&client_addr,&client_len);
				printf("新连接的客户端的ip = %s\n",inet_ntoa(client_addr.sin_addr));
				printf("新连接的客户端的port = %d\n",ntohs(client_addr.sin_port));

				struct epoll_event epoll_client = {events : EPOLLIN , data:{fd : client}};
				epoll_ctl(epfd,EPOLL_CTL_ADD,client,&epoll_client);
				eplen ++;
	

				continue;
			}

			// 剩下的都是客户端描述符
			bool res = client_handler(fd,db);// 这个函数用来写处理客户端的逻辑
			if(res == false){
				epoll_ctl(epfd,EPOLL_CTL_DEL,fd,nullptr);
			}
		}
		
	}
	return 0;
}

bool client_handler(int client,dbHelper& db){
	while(1){
		int size = 0;
		int res = 0;
		Pack pack;
	
		if(m[client].unreaded_pack_size != 0){
			res=recv(client,(char*)&m[client].readed_pack + m[client].readed_pack_size,m[client].unreaded_pack_size,MSG_DONTWAIT);
			if(res != m[client].unreaded_pack_size){
				// 这里只要更新下已读大小和未读大小，保证下一次进入当前分支的时候，能够根据已读大小和未读大小，读取对应的数据以及存放到对应的地方
				m[client].readed_pack_size += res;
				m[client].unreaded_pack_size -= res;
				break;
			}

			pack = m[client].readed_pack;
			// 处理完分包记得 unreaded_pack_size = 0;
			m[client].unreaded_pack_size = 0;
		}else{

			if(m[client].unreaded_size_size != 0){
				recv(client,(char*)&m[client].readed_size + m[client].readed_size_size,m[client].unreaded_size_size,MSG_DONTWAIT);
				size = m[client].readed_size;
				m[client].unreaded_size_size = 0;
			}else{

				// else 部分为正常读取数据：先读4字节，再读剩余字节数，可能处理分包
				res = recv(client,(char*)&size,4,MSG_DONTWAIT);
				if(res == -1){
					//cout << "退出循环" << endl;
					return true;
				}else if(res == 0){
					cout << "4字节recv结束" << endl;
					return false;
				}

				if(res != 4){
					memcpy(&m[client].readed_size,&size,m[client].readed_size_size);
					m[client].readed_size_size = res;
					m[client].unreaded_size_size = 4 - res;
					break;
				}
			}


			res = recv(client,(char*)&pack+4,size-4,MSG_DONTWAIT);
			if(res == 0){
				cout << "size-4字节recv结束" << endl;
				return false;
			}else if(res == -1){
				return true;
			}
			pack.setSize(size);


			if(res != size-4){
				// 如果实际读取到的字节数 != 想要读取的字节数
				// 说明发生了分包
				cout << "发生分包" << endl;
				memcpy(&m[client].readed_pack,&pack,m[client].readed_pack_size);// 将已经读取的协议包缓存在每个客户端专属的缓存区 readed_pack 里面
				m[client].readed_pack_size = res + 4;
				m[client].unreaded_pack_size = size - m[client].readed_pack_size;
				break;
			}
		}



		switch(pack.getType()){
			case TYPE_REGIST:{
				vector<string> list = pack.readAll();
				string name = list[0];
				string pswd = list[1];
				bool res = db.regist(name,pswd);
				if(res == true){
					pack.setBack(BACK_SUCCESS);
				}else{
					pack.setBack(BACK_ERR);
				}
				pack >> client; // 将协议包回给客户端
				break;
			}
			case TYPE_LOGIN:{
				vector<string> list = pack.readAll();
				string name = list[0];
				string pswd = list[1];
				bool res = db.login(name,pswd);
				if(res == true){
					pack.setBack(BACK_SUCCESS);
					m[client].username = name;
				}else{
					pack.setBack(BACK_ERR);
				}
				pack >> client; // 将协议包回给客户端
				break;
			}

			case TYPE_FILE_UPLOAD_REQUEST:{
				cout << "文件上传请求" << endl;
				vector<string> list = pack.readAll();
				string filename = list[0];
				m[client].fp = fopen(filename.data(),"w");
				break;
			}
			case TYPE_FILE_UPLOADING:{
				cout << "文件上传中" << endl;
				char buf[4096] = "";
				pack.readAll(buf,pack.size()-12);
				// 到此为止，客户端发来的一部分的文件内容，保存到了buf里面
				fwrite(buf,1,pack.size()-12,m[client].fp);
				break;
			}
			case TYPE_FILE_UPLOAD_END:{
				cout << "文件上传完成" << endl;
				fclose(m[client].fp);
				break;
			}
			case TYPE_SENDING_CAMERA:
			case TYPE_SEND_CAMERA_END:{
				// 服务器只做一个事情：将接受到的所有图片内容，转发给其他所有客户端
				cout << "转发camera图片..." << endl;
				for(auto& ele:m){
					if(ele.first != client){
						pack >> ele.first;
					}
				}
				break;
			}

			// 在这里新写 2 个case，用来转发桌面画面

		}
		//cout << "数据处理完毕" << endl;
	}
	return true;
}























