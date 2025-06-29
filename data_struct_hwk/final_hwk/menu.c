#include "common.h"


user* regist()
{
    user* user1 = (user*)malloc(sizeof(user));
    printf("********  注册账号  ********\n");
    printf("请输入用户名：");
    fgets(user1->username, 15, stdin);
    user1->username[strcspn(user1->username, "\n")] = '\0';
    printf("请输入密码：");
    fgets(user1->passwd, 15, stdin);
    user1->passwd[strlen(user1->passwd) - 1] = '\0';
    return user1;
}

int is_user()
{
    user* user1 = regist();
    char username1[15], passwd1[15];
    int i;
    printf("*****  通讯录管理系统  *****\n");
    for ( ; ; ) {
        printf("请输入账号：");
        fgets(username1, 15, stdin);
        username1[strcspn(username1, "\n")] = '\0';
        if (strcmp(username1, user1->username)) printf("账号错误，请重新输入");
        else break;
    }
    for (i = 0; i < 3; i++) {
        printf("请输入密码：");
        fgets(passwd1, 15, stdin);
        passwd1[strlen(passwd1) - 1] = '\0';
        if (strcmp(passwd1, user1->passwd)) printf("密码错误，请重新输入");
        else {
            printf("登陆成功！\n");
            break;
        }
    }
    if (i == 3) {
        printf("\n错误次数过多，已被限制登陆！\n");
        free(user1);
        exit(0);
    }
    else {
        free(user1);
        return 0;
    }
}
void p_menu()
{
    printf("     *****************  通讯录管理系统  ****************     \n");
    printf("     ***************************************************     \n");
    printf("     *                   1.录入信息                    *     \n");
    printf("     *                   2.查找信息                    *     \n");
    printf("     *                   3.修改信息                    *     \n");
    printf("     *                   4.删除信息                    *     \n");
    printf("     *                   5.展示信息                    *     \n");
    printf("     *                   6.退出系统                    *     \n");
    printf("     ***************************************************     \n");
    printf("     *          <C> 2025.06.28 By Xuanzhonglu          *     \n");
    printf("     ***************************************************      \n");
    printf("\n\n");
}

//新建联系人
void increase(node* H)
{
    int num;
    printf("请输入需要添加的人数：");
    scanf("%d", &num);
    getchar();
    for (int i = 1; i <= num; i++) {
        person new_person;
        printf("请输入第%d个联系人的姓名：\n", i);
        fgets(new_person.name, 15, stdin);
        new_person.name[strcspn(new_person.name, "\n")] = '\0';
        printf("请输入第%d个联系人的联系方式：\n", i);
        fgets(new_person.phone, 15, stdin);
        new_person.phone[strcspn(new_person.phone, "\n")] = '\0';
        insert_tail(H, new_person);
    }
}

//展示所有联系人
void show_all(node* H)
{
    if (!H || H->len == 0) {
        printf("通讯录为空！\n");
        return;
    }
    
    printf("\n     ================= 通讯录（共%d人）=================     \n", H->len);
    node* p = H->next;
    int count = 1;
    
    for ( ; p; ) {
        printf("         %d. 姓名: %-15s 电话: %-15s\n", 
               count++, p->data.name, p->data.phone);
        p = p->next;
    }
    printf("     ==================================================     \n\n");
}

//删除联系人
void delete(node* H)
{
    if (!H || H->len == 0) {
        printf("通讯录为空，无法删除！\n");
        return;
    }
    char name[15];
    printf("     =================  当前通讯录为  =================     \n");
    show_all(H);
    printf("请输入要删除的联系人姓名：");
    if (!fgets(name, 15, stdin)) return;
    name[strcspn(name, "\n")] = '\0';
    
    node* p = H;
    node* q = H->next;
    int found = 0;
    
    for ( ; q; ) {
        if (strcmp(q->data.name, name) == 0) {
            p->next = q->next;
            free(q);
            H->len--;
            found = 1;
            printf("已删除联系人: %s\n", name);
            break;
        }
        p = q;
        q = q->next;
    }
    
    if (!found) {
        printf("未找到联系人: %s\n", name);
    }
}

//查找联系人
void search(node* H)
{
    if (!H || H->len == 0) {
        printf("通讯录为空，无法查找！\n");
        return;
    }
    
    char name[15];
    printf("请输入要查找的联系人姓名：");
    if (!fgets(name, 15, stdin)) return;
    name[strcspn(name, "\n")] = '\0';
    
    node* p = H->next;
    int found = 0;
    
    printf("\n     =================    查找结果    =================     \n");
    for ( ; p; ) {
        if (strcmp(p->data.name, name) == 0) {
            printf("         姓名: %-15s 电话: %-15s\n", 
                   p->data.name, p->data.phone);
            found = 1;
        }
        p = p->next;
    }
    
    if (!found) {
        printf("未找到联系人: %s\n", name);
    }
    printf("     ==================================================     \n\n");
}

//修改联系方式
void change(node* H)
{
    if (!H || H->len == 0) {
        printf("通讯录为空，无法修改！\n");
        return;
    }
    
    char name[15];
    printf("请输入要修改的联系人姓名：");
    if (!fgets(name, 15, stdin)) return;
    name[strcspn(name, "\n")] = '\0';
    
    node* p = H->next;
    int found = 0;
    
    for ( ; p; ) {
        if (strcmp(p->data.name, name) == 0) {
            char new_phone[15];
            printf("找到联系人: %s\n当前电话: %s\n", name, p->data.phone);
            printf("请输入新电话号码：");
            
            if (fgets(new_phone, 15, stdin)) {
                new_phone[strcspn(new_phone, "\n")] = '\0';
                strcpy(p->data.phone, new_phone);
                printf("联系方式已更新！\n");
                found = 1;
                break;
            } else {
                printf("输入无效！\n");
                return;
            }
        }
        p = p->next;
    }
    
    if (!found) {
        printf("未找到联系人: %s\n", name);
    }
}

int main_menu(node* H)
{
    int choice;
    while (1) {
        p_menu();
        printf("请选择操作 (1-7): ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // 清空无效输入
            printf("输入无效，请重新选择！\n");
            continue;
        }
        getchar(); // 消耗换行符
        
        switch (choice) {
            case 1: 
                increase(H);   //录入联系人
                break;
            case 2: 
                search(H);     // 按姓名查找
                break;
            case 3: 
                change(H);     //按姓名修改
                break;
            case 4: 
                delete(H);     // 按姓名删除
                break;
            case 5: 
                show_all(H);   //打印通讯录
                break;
            case 6: 
                printf("已退出系统\n");
                free_list(H);
                exit(0);
            default:
                printf("无效选择，请重新输入！\n");
        }
    }
}