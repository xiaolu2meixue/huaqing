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
    int msqid = msgget(key, IPC_CREAT | 0666);
    
    for(int i = 1; ; i++) {
        struct msgbuf msg;
        msg.mtype = i;
        
        printf("Enter name: ");
        fgets(msg.name, 100, stdin);
        msg.name[strcspn(msg.name, "\n")] = '\0';
        
        if (strcmp(msg.name, "quit") == 0) {
            // 发送退出消息
            msg.age = -1;  // 使用age=-1作为退出标志
            msgsnd(msqid, &msg, sizeof(struct msgbuf) - sizeof(long), 0);
            break;
        }
        
        printf("Enter age: ");
        scanf("%d", &msg.age);
        getchar(); // 清除输入缓冲区中的换行符
        
        printf("Enter height: ");
        scanf("%f", &msg.high);
        getchar(); // 清除输入缓冲区中的换行符
        
        // 发送整个结构体，减去mtype的大小
        msgsnd(msqid, &msg, sizeof(struct msgbuf) - sizeof(long), 0);
        
        printf("Message sent (type %ld): %s, %d, %.2f\n", 
               msg.mtype, msg.name, msg.age, msg.high);
    }
    return 0;
}