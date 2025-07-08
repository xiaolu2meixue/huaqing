#include <myhead.h>

// 定义 semun 联合体
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// P操作 - 申请资源
int P(int semid, int sem_num) {
    struct sembuf op = {sem_num, -1, SEM_UNDO}; 
    if (semop(semid, &op, 1) < 0) {
        ERRLOG("semop P failed");
    }
}

// V操作 - 释放资源
int V(int semid, int sem_num) {
    struct sembuf op = {sem_num, 1, SEM_UNDO};
    if (semop(semid, &op, 1) < 0) {
        ERRLOG("semop V failed");
    }
}

int main(int argc, const char* argv[])
{
    key_t key = ftok("/home/ubuntu/git_test/huaqing/IO-Threads_and_Processes/day7/", 'a');
    if (key == -1) ERRLOG("ftok error");

    // 创建信号量集 (包含2个信号量)
    // 0号信号量：控制写操作 (初始为1，表示可写)
    // 1号信号量：控制读操作 (初始为0，表示无数据可读)
    int semid = semget(key, 2, IPC_CREAT | 0666);
    if (semid == -1) ERRLOG("semget error");
    
    // 初始化信号量
    union semun arg;
    unsigned short values[2] = {1, 0}; // 写信号量=1, 读信号量=0
    arg.array = values;
    if (semctl(semid, 0, SETALL, arg) == -1) ERRLOG("semctl SETALL error");

    int shmid = shmget(key, 128, IPC_CREAT | 0664);
    if (shmid == -1) ERRLOG("shmget error");
    void* shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void*)-1) ERRLOG("shmat error");
    
    char* buf = (char*)shmaddr;
    
    for ( ; ; ) {
        // 等待可写信号 (P操作)
        P(semid, 0);
        
        // 写入数据
        fgets(buf, 128, stdin);
        buf[strcspn(buf, "\n")] = '\0';
        
        // 通知可读信号 (V操作)
        V(semid, 1);
        
        //退出条件
        if (strcmp(buf, "quit") == 0) break;

        sleep(1);
    }
    
    // 断开映射
    if (shmdt(shmaddr) == -1) ERRLOG("shmdt error");
    
    // 删除共享内存
    if (shmctl(shmid, IPC_RMID, NULL) == -1) ERRLOG("shmctl error");
    
    // 删除信号量集
    if (semctl(semid, 0, IPC_RMID) == -1) ERRLOG("semctl RMID error");

    return 0;
}