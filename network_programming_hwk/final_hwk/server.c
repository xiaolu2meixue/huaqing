#include <myhead.h>
#include <sqlite3.h>

enum Type {
    TYPE_REGIST,
    TYPE_LOGIN
};

enum Err {
    SUCCESS,
    ERR_NAME,
    ERR_PSWD
};

typedef struct Pack {
    enum Type type;
    enum Err err;
    char name[16];
    char pswd[16];
} pack_t;

void regist(pack_t pack, int client, sqlite3* db)
{
    sqlite3_stmt* stmt = NULL;
    char* errmsg = NULL;
    char* sql = "insert into users(name,pswd) values(?,?)";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, pack.name, -1, NULL);
    sqlite3_bind_text(stmt, 2, pack.pswd, -1, NULL);

    int res = sqlite3_step(stmt);
    if (res == SQLITE_DONE) {
        // 注册成功
        pack.err = SUCCESS;
    }
    else {
        // 注册失败
        pack.err = ERR_NAME;
    }
    //pack.type = TYPE_REGIST;
    write(client, &pack, sizeof(pack));
}

void login(pack_t pack, int client, sqlite3* db)
{
    sqlite3_stmt* stmt = NULL;
    char* errmsg = NULL;
    char* sql = "select pswd from users where name = ?";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, pack.name, -1, NULL);

    int res = sqlite3_step(stmt);
    if (res == SQLITE_DONE) {
        pack.err = ERR_NAME;
    }
    else {
        const char* db_pswd = (const char*)sqlite3_column_text(stmt, 0);
        if (strcmp(db_pswd, pack.pswd) == 0) {
            pack.err = SUCCESS;
        }
        else {
            pack.err = ERR_PSWD;
        }
    }
    write(client, &pack, sizeof(pack));
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        printf("请输入端口号\n");
        return 1;
    }
    short port = atoi(argv[1]);
    // "abc123" -> 0
    int server = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        return 1;
    }
    listen(server, 10);

    sqlite3* db = NULL;
    sqlite3_open("./test.db", &db);

    // 创建epoll监视列表
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    // 将 0 和 server 添加进入监视列表
    struct epoll_event epoll_stdin = {.events = EPOLLIN , .data.fd = 0};
    struct epoll_event epoll_server = {.events = EPOLLIN , .data.fd = server};

    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &epoll_stdin);
    epoll_ctl(epfd, EPOLL_CTL_ADD, server, &epoll_server);
    int eplen = 2;

    while(1) {
        // 提前准备一个激活列表
        struct epoll_event list[20] = {0};
        int count = epoll_wait(epfd, list, eplen, -1);

        for(int i = 0; i < count; i++) {
            // list里面全部是激活的描述符，最多判断一下，以何种方式激活的

            // 将激活的具体描述符单独取出
            int fd = list[i].data.fd;
            if(fd == 0) {
                char buf[1024] = "";
                scanf("%s", buf);
                getchar();
                printf("键盘输入数据:%s\n", buf);
                continue;
            }

            if(fd == server) {
                printf("有客户端连接\n");
                struct sockaddr_in client_addr = {0};
                socklen_t client_len = sizeof(client_addr);
                int client = accept(server, (struct sockaddr*)&client_addr, &client_len);
                printf("新连接的客户端的ip = %s\n", inet_ntoa(client_addr.sin_addr));
                printf("新连接的客户端的port = %d\n", ntohs(client_addr.sin_port));

                struct epoll_event epoll_client = {.events = EPOLLIN | EPOLLET , .data.fd = client};
                epoll_ctl(epfd, EPOLL_CTL_ADD, client, &epoll_client);
                eplen++;

                continue;
            }

            // 剩下的都是客户端描述符
            pack_t pack = {0};
            int res = read(fd, &pack, sizeof(pack));
            if(res == 0) {
                printf("客户端断开连接\n");
                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                close(fd);
                eplen--;
                continue;
            }

            switch(pack.type) {
                case TYPE_REGIST: {
                    regist(pack, fd, db);
                    break;
                }
                case TYPE_LOGIN: {
                    login(pack, fd, db);
                    break;
                }
            }
        }
    }

    sqlite3_close(db);
    close(server);
    return 0;
}