#include <myhead.h>
#include <sqlite3.h>
#include <time.h>

enum Type {
    TYPE_DOC_REGIST,       // 医生注册
    TYPE_DOC_LOGIN,        // 医生登录
    TYPE_PAT_REGIST,       // 病人注册
    TYPE_PAT_LOGIN,        // 病人登录
    TYPE_QUERY_CASE,       // 查询病例
    TYPE_UPDATE_CASE,      // 更新病例
    TYPE_PATIENT_QUERY_CASE // 病人查询病例
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

// 病例记录结构
typedef struct CaseRecord {
    char date[20];          // 日期时间
    char doctor[16];        // 接诊医生
    char patient_desc[256]; // 病人口述
    char diagnosis[256];    // 医生诊断
    char prescription[256]; // 医生开药
    char advice[256];       // 医生医嘱
} case_record_t;

// 医生注册
void doc_regist(pack_t pack, int client, sqlite3* db)
{
    sqlite3_stmt* stmt = NULL;
    char* sql = "insert into users(name,pswd) values(?,?)";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, pack.name, -1, NULL);
    sqlite3_bind_text(stmt, 2, pack.pswd, -1, NULL);

    int res = sqlite3_step(stmt);
    if (res == SQLITE_DONE) {
        pack.err = SUCCESS;
    } else {
        pack.err = ERR_NAME;
    }
    write(client, &pack, sizeof(pack));
    sqlite3_finalize(stmt);
}

// 医生登录
void doc_login(pack_t pack, int client, sqlite3* db)
{
    sqlite3_stmt* stmt = NULL;
    char* sql = "select pswd from users where name = ?";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, pack.name, -1, NULL);

    int res = sqlite3_step(stmt);
    if (res == SQLITE_DONE) {
        pack.err = ERR_NAME;
    } else {
        const char* db_pswd = (const char*)sqlite3_column_text(stmt, 0);
        if (strcmp(db_pswd, pack.pswd) == 0) {
            pack.err = SUCCESS;
        } else {
            pack.err = ERR_PSWD;
        }
    }
    write(client, &pack, sizeof(pack));
    sqlite3_finalize(stmt);
}

// 病人注册
void pat_regist(pack_t pack, int client, sqlite3* db)
{
    sqlite3_stmt* stmt = NULL;
    char* sql = "insert into pusers(name,pswd) values(?,?)";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, pack.name, -1, NULL);
    sqlite3_bind_text(stmt, 2, pack.pswd, -1, NULL);

    int res = sqlite3_step(stmt);
    if (res == SQLITE_DONE) {
        // 注册成功，创建病人表
        pack.err = SUCCESS;
        char create_table_sql[512];
        snprintf(create_table_sql, sizeof(create_table_sql),
                "CREATE TABLE IF NOT EXISTS \"%s\" ("
                "date TEXT PRIMARY KEY,"
                "doctor TEXT,"
                "patient_desc TEXT,"
                "diagnosis TEXT,"
                "prescription TEXT,"
                "advice TEXT);", pack.name);
                
        char *errmsg = NULL;
        if (sqlite3_exec(db, create_table_sql, NULL, NULL, &errmsg)) {
            fprintf(stderr, "创建表失败: %s\n", errmsg);
            sqlite3_free(errmsg);
        }
    } else {
        pack.err = ERR_NAME;
    }
    write(client, &pack, sizeof(pack));
    sqlite3_finalize(stmt);
}

// 病人登录
void pat_login(pack_t pack, int client, sqlite3* db)
{
    sqlite3_stmt* stmt = NULL;
    char* sql = "select pswd from pusers where name = ?";
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, pack.name, -1, NULL);

    int res = sqlite3_step(stmt);
    if (res == SQLITE_DONE) {
        pack.err = ERR_NAME;
    } else {
        const char* db_pswd = (const char*)sqlite3_column_text(stmt, 0);
        if (strcmp(db_pswd, pack.pswd) == 0) {
            pack.err = SUCCESS;
        } else {
            pack.err = ERR_PSWD;
        }
    }
    write(client, &pack, sizeof(pack));
    sqlite3_finalize(stmt);
}

// 查询病例
void query_case(int client, sqlite3* db, const char* patient_name)
{
    sqlite3_stmt* stmt = NULL;
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM \"%s\" ORDER BY date DESC;", patient_name);
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        int count = 0;
        write(client, &count, sizeof(int)); // 发送0条记录
        return;
    }

    // 获取记录数量
    int count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) count++;
    write(client, &count, sizeof(int));
    sqlite3_reset(stmt);

    // 发送记录
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        case_record_t record;
        strncpy(record.date, (const char*)sqlite3_column_text(stmt, 0), sizeof(record.date));
        strncpy(record.doctor, (const char*)sqlite3_column_text(stmt, 1), sizeof(record.doctor));
        strncpy(record.patient_desc, (const char*)sqlite3_column_text(stmt, 2), sizeof(record.patient_desc));
        strncpy(record.diagnosis, (const char*)sqlite3_column_text(stmt, 3), sizeof(record.diagnosis));
        strncpy(record.prescription, (const char*)sqlite3_column_text(stmt, 4), sizeof(record.prescription));
        strncpy(record.advice, (const char*)sqlite3_column_text(stmt, 5), sizeof(record.advice));
        
        write(client, &record, sizeof(case_record_t));
    }
    sqlite3_finalize(stmt);
}

// 更新病例
void update_case(int client, sqlite3* db, const char* patient_name)
{
    case_record_t record;
    read(client, &record, sizeof(case_record_t));
    
    // 获取当前时间
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(record.date, sizeof(record.date), "%04d-%02d-%02d %02d:%02d:%02d",
            t->tm_year+1900, t->tm_mon+1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
    
    // 插入记录
    sqlite3_stmt* stmt = NULL;
    char sql[512];
    snprintf(sql, sizeof(sql), 
            "INSERT INTO \"%s\" (date, doctor, patient_desc, diagnosis, prescription, advice) "
            "VALUES (?, ?, ?, ?, ?, ?);", patient_name);
            
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, record.date, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, record.doctor, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, record.patient_desc, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, record.diagnosis, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, record.prescription, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, record.advice, -1, SQLITE_STATIC);
    
    int success = 0;
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        success = 1;
    }
    sqlite3_finalize(stmt);
    
    // 返回操作结果
    write(client, &success, sizeof(int));
    
    // 验证更新：重新获取病例
    if (success) {
        query_case(client, db, patient_name);
    }
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        printf("请输入端口号\n");
        return 1;
    }
    short port = atoi(argv[1]);
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
    
    // 创建用户表
    char *errmsg;
    const char *create_user_sql = "CREATE TABLE IF NOT EXISTS users ("
                                  "name TEXT PRIMARY KEY,"
                                  "pswd TEXT);";
    sqlite3_exec(db, create_user_sql, NULL, NULL, &errmsg);
    
    // 创建病人用户表
    const char *create_puser_sql = "CREATE TABLE IF NOT EXISTS pusers ("
                                   "name TEXT PRIMARY KEY,"
                                   "pswd TEXT);";
    sqlite3_exec(db, create_puser_sql, NULL, NULL, &errmsg);

    int epfd = epoll_create1(EPOLL_CLOEXEC);
    struct epoll_event epoll_stdin = {.events = EPOLLIN , .data.fd = 0};
    struct epoll_event epoll_server = {.events = EPOLLIN , .data.fd = server};

    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &epoll_stdin);
    epoll_ctl(epfd, EPOLL_CTL_ADD, server, &epoll_server);
    int eplen = 2;

    while(1) {
        struct epoll_event list[20] = {0};
        int count = epoll_wait(epfd, list, eplen, -1);

        for(int i = 0; i < count; i++) {
            int fd = list[i].data.fd;
            if(fd == 0) {
                char buf[1024] = "";
                scanf("%s", buf);
                getchar();
                printf("键盘输入数据:%s\n", buf);
                continue;
            }

            if(fd == server) {
                struct sockaddr_in client_addr = {0};
                socklen_t client_len = sizeof(client_addr);
                int client = accept(server, (struct sockaddr*)&client_addr, &client_len);

                struct epoll_event epoll_client = {.events = EPOLLIN | EPOLLET , .data.fd = client};
                epoll_ctl(epfd, EPOLL_CTL_ADD, client, &epoll_client);
                eplen++;
                continue;
            }

            pack_t pack;
            int res = read(fd, &pack, sizeof(pack));
            if(res <= 0) {
                if (res == 0) {
                    printf("客户端断开连接\n");
                }
                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                close(fd);
                eplen--;
                continue;
            }

            switch(pack.type) {
                case TYPE_DOC_REGIST: {
                    doc_regist(pack, fd, db);
                    break;
                }
                case TYPE_DOC_LOGIN: {
                    doc_login(pack, fd, db);
                    break;
                }
                case TYPE_PAT_REGIST: {
                    pat_regist(pack, fd, db);
                    break;
                }
                case TYPE_PAT_LOGIN: {
                    pat_login(pack, fd, db);
                    break;
                }
                case TYPE_QUERY_CASE: {
                    char patient_name[16];
                    read(fd, patient_name, sizeof(patient_name));
                    query_case(fd, db, patient_name);
                    break;
                }
                case TYPE_UPDATE_CASE: {
                    char patient_name[16];
                    read(fd, patient_name, sizeof(patient_name));
                    update_case(fd, db, patient_name);
                    break;
                }
                case TYPE_PATIENT_QUERY_CASE: {
                    // 病人查询自己的病例，使用登录的病人名作为表名
                    query_case(fd, db, pack.name);
                    break;
                }
            }
        }
    }

    sqlite3_close(db);
    close(server);
    return 0;
}