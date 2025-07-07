#include <myhead.h>

struct msgbuf {
    long mtype;
    char name[100];
    int age;
    float high;
};

int main()
{
    key_t key = ftok("/tmp", 'A');
    int msqid = msgget(key, 0666);
    
    for (int i = 1; ; i++) {
        struct msgbuf msg;
        // 接收整个结构体，减去mtype的大小
        msgrcv(msqid, &msg, sizeof(struct msgbuf) - sizeof(long), i, 0);

        if (msg.age == -1) {  // 检查退出标志
            printf("Received exit signal. Exiting...\n");
            break;
        }
        
        printf("Received message (type %ld):\n", msg.mtype);
        printf("Name: %s\n", msg.name);
        printf("Age: %d\n", msg.age);
        printf("Height: %.2f\n", msg.high);
    }
    
    msgctl(msqid, IPC_RMID, NULL); // 删除消息队列
    return 0;
}