#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#define MAX_LINE_LEN 1024
#define MAX_THREADS 4
#define MAX_PROCESSES 2
#define SHM_SIZE 1024
#define MSG_TYPE_WORK 1
#define MSG_TYPE_EXIT 2

// 消息结构体
typedef struct {
    long mtype;
    char mtext[MAX_LINE_LEN];
} LogMessage;

// 共享内存结构
typedef struct {
    pthread_mutex_t mutex;
    int char_count[256];
    int active;
} SharedData;

// 线程参数
typedef struct {
    int msg_id;
    SharedData *shm_data;
} ThreadArg;

// 消息队列ID
int msg_id;
// 共享内存ID
int shm_id;

// 线程工作函数
void *thread_worker(void *arg) {
    ThreadArg *targ = (ThreadArg *)arg;
    LogMessage msg;

    while (1) {
        // 接收消息
        if (msgrcv(targ->msg_id, &msg, sizeof(msg.mtext), 0, 0) == -1) {
            perror("msgrcv");
            break;
        }

        // 检查退出消息
        if (msg.mtype == MSG_TYPE_EXIT) {
            break;
        }

        // 处理日志行
        char *line = msg.mtext;
        pthread_mutex_lock(&targ->shm_data->mutex);
        for (int i = 0; line[i] != '\0'; i++) {
            unsigned char c = line[i];
            targ->shm_data->char_count[c]++;
        }
        pthread_mutex_unlock(&targ->shm_data->mutex);
    }

    pthread_exit(NULL);
}

// 子进程函数
void child_process(int process_id) {
    // 附加共享内存
    SharedData *shm_data = (SharedData *)shmat(shm_id, NULL, 0);
    if (shm_data == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // 创建线程池
    pthread_t threads[MAX_THREADS];
    ThreadArg targs[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; i++) {
        targs[i].msg_id = msg_id;
        targs[i].shm_data = shm_data;
        if (pthread_create(&threads[i], NULL, thread_worker, &targs[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // 等待线程结束
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 分离共享内存
    shmdt(shm_data);
    exit(EXIT_SUCCESS);
}

// 监控进程函数
void monitor_process() {
    // 附加共享内存
    SharedData *shm_data = (SharedData *)shmat(shm_id, NULL, 0);
    if (shm_data == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    while (shm_data->active) {
        sleep(1);  // 每秒刷新一次
        system("clear");  // 清屏
        
        printf("\033[1;32m");  // 设置绿色文本
        printf("=== 实时字符频率统计 === (进程ID: %d)\n", getpid());
        printf("\033[0m");  // 重置文本样式
        
        pthread_mutex_lock(&shm_data->mutex);
        for (int i = 32; i < 127; i++) {  // 只显示可打印字符
            if (shm_data->char_count[i] > 0) {
                printf("字符 '%c' (%3d): %6d 次\n", 
                      (char)i, i, shm_data->char_count[i]);
            }
        }
        pthread_mutex_unlock(&shm_data->mutex);
        
        printf("\n按 Ctrl+C 退出监控...\n");
    }

    shmdt(shm_data);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "用法: %s <日志文件>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 创建消息队列
    key_t msg_key = ftok("/tmp", 'A');
    msg_id = msgget(msg_key, IPC_CREAT | 0666);
    if (msg_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // 创建共享内存
    key_t shm_key = ftok("/tmp", 'B');
    shm_id = shmget(shm_key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        msgctl(msg_id, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    // 附加并初始化共享内存
    SharedData *shm_data = (SharedData *)shmat(shm_id, NULL, 0);
    if (shm_data == (void *)-1) {
        perror("shmat");
        msgctl(msg_id, IPC_RMID, NULL);
        shmctl(shm_id, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }

    memset(shm_data, 0, SHM_SIZE);
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&shm_data->mutex, &mutex_attr);
    shm_data->active = 1;

    // 创建监控进程
    pid_t monitor_pid = fork();
    if (monitor_pid == 0) {
        monitor_process();
    } else if (monitor_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // 创建子进程
    pid_t child_pids[MAX_PROCESSES];
    for (int i = 0; i < MAX_PROCESSES; i++) {
        child_pids[i] = fork();
        if (child_pids[i] == 0) {
            child_process(i);
        } else if (child_pids[i] < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    // 主进程读取日志文件
    FILE *log_file = fopen(argv[1], "r");
    if (!log_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    LogMessage msg;
    msg.mtype = MSG_TYPE_WORK;

    while (fgets(line, MAX_LINE_LEN, log_file)) {
        strncpy(msg.mtext, line, MAX_LINE_LEN);
        if (msgsnd(msg_id, &msg, sizeof(msg.mtext), 0) == -1) {
            perror("msgsnd");
        }
    }

    fclose(log_file);

    // 发送退出消息
    msg.mtype = MSG_TYPE_EXIT;
    for (int i = 0; i < MAX_PROCESSES * MAX_THREADS; i++) {
        msgsnd(msg_id, &msg, sizeof(msg.mtext), 0);
    }

    // 等待子进程结束
    for (int i = 0; i < MAX_PROCESSES; i++) {
        waitpid(child_pids[i], NULL, 0);
    }

    // 通知监控进程退出
    sleep(2);  // 给监控进程最后刷新时间
    shm_data->active = 0;
    kill(monitor_pid, SIGTERM);
    waitpid(monitor_pid, NULL, 0);

    // 清理资源
    msgctl(msg_id, IPC_RMID, NULL);
    shmdt(shm_data);
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}