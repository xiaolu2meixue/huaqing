#include <myhead.h>

// P操作 - 申请资源
int P(int semid, int sem_num)
{
    struct sembuf op = {sem_num, -1, SEM_UNDO};
    if (semop(semid, &op, 1) < 0) ERRLOG("semop P error");
}

// V操作 - 释放资源
int V(int semid, int sem_num)
{
    struct sembuf op = {sem_num, 1, SEM_UNDO};
    if (semop(semid, &op, 1) < 0) ERRLOG("semop V error");
}

int main()
{
    key_t key;
    int shmid, semid;
    void *shmaddr;
    
    // 1. 创建键值
    if ((key = ftok("/home/ubuntu/git_test/huaqing/IO-Threads_and_Processes/day7/", 'a')) == -1) {
        ERRLOG("ftok error");
    }
    
    // 2. 获取信号量集
    if ((semid = semget(key, 2, 0666)) == -1) {
        ERRLOG("semget error");
    }
    
    // 3. 获取共享内存
    if ((shmid = shmget(key, 128, 0666)) == -1) {
        ERRLOG("shmget error");
    }
    
    // 4. 映射共享内存
    if ((shmaddr = shmat(shmid, NULL, SHM_RDONLY)) == (void*)-1) {
        ERRLOG("shmat error");
    }
    
    char *buf = (char*)shmaddr;
    
    while (1) {
        // 等待可读信号 (P操作)
        P(semid, 1);
        
        // 读取数据
        if (strcmp(buf, "quit") == 0) break;
        printf("%s\n", buf);
        
        // 通知可写信号 (V操作)
        V(semid, 0);
        
        sleep(1); // 模拟处理时间
    }
    
    // 5. 断开映射
    if (shmdt(shmaddr) == -1) {
        ERRLOG("shmdt error");
    }
    
    return 0;
}