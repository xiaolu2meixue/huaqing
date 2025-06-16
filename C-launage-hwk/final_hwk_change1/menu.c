
#include "manager.h"

Class* class;

void p_menu()
{

    printf("     **************************************************    \n");
 
    printf("       *       学生成绩管理系统————帮助菜单         *  \n");
 
    printf("     **************************************************      \n");
    printf("\n");
    printf("       *            1:录入学生信息                  *  \n");
 
    printf("       *            2:删除学生信息                  *  \n");
 
    printf("       *            3:修改学生信息                  *  \n");
 
    printf("       *            4:查找学生信息                  *  \n");
 
    printf("       *            5:显示所有学生信息列表          *  \n");
 
    printf("       *            6:退出系统                      *  \n");
    printf("\n");
    printf("     **************************************************      \n");
 
    printf("       *        <C> 2025.06.14 By Xuanzhonglu       *  \n");
 
    printf("     **************************************************      \n");
    printf("\n\n");
}

void increase(Class* myclass)
{

    int num; int class_num = 0;;
    printf("请输入需要录入学生数：\n");
    scanf("%d", &num);
    getchar();
    printf("请输入加入的班级：\n");
    scanf("%d", &class_num);
    for (int i = 1; i <= num; i++)
    {
        printf("请输入第%d个学生id：\n", i);
        scanf("%d", &(myclass[class_num].c_student[myclass[class_num].member].id));
        getchar();

        printf("请输入第%d个学生姓名：\n", i);
        fgets(myclass[class_num].c_student[myclass[class_num].member].name, 10, stdin);
        myclass[class_num].c_student[myclass[class_num].member].name[strlen(myclass[class_num].c_student[myclass[class_num].member].name) - 1] = 0;

        printf("请输入第%d个学生密码：\n", i);
        fgets(myclass[class_num].c_student[myclass[class_num].member].passwd, 10, stdin);
        myclass[class_num].c_student[myclass[class_num].member].passwd[strlen(myclass[class_num].c_student[myclass[class_num].member].passwd) - 1] = 0;

        
        printf("请输入第%d个学生的年龄：\n", i);
        scanf("%d", &(myclass[class_num].c_student[myclass[class_num].member].age));
        getchar();

        printf("请输入第%d个学生的年级：\n", i);
        scanf("%d", &(myclass[class_num].c_student[myclass[class_num].member].grade));
        getchar();

        printf("请输入第%d个学生的数学成绩：\n", i);
        scanf("%d", &(myclass[class_num].c_student[myclass[class_num].member].scores.math_score));
        getchar();

        printf("请输入第%d个学生的C语言成绩：\n", i);
        scanf("%d", &(myclass[class_num].c_student[myclass[class_num].member].scores.C_score));
        getchar();

        printf("请输入第%d个学生的语文成绩：\n", i);
        scanf("%d", &(myclass[class_num].c_student[myclass[class_num].member].scores.chinese_score));
        getchar();

        printf("请输入第%d个学生的英语成绩：\n", i);
        scanf("%d", &(myclass[class_num].c_student[myclass[class_num].member].scores.english_score));
        getchar();
        
        myprint(myclass[class_num].c_student[myclass[class_num].member]);
        myclass[class_num].member++;
    }
}

int main_menu()
{
    int num;
    //class = init(class, 10);

    p_menu(); 
	printf("您好，请输入菜单编号：");
	scanf("%d", &num);
	switch (num) {
		case 1: 
            increase(class);
            break;
		// case 2: delete(); break;
		// case 3: change(); break;
		// case 4: seek(); break;
		// case 5: show_all(); break;
		case 6: printf("退出系统成功\n"); 
            exit(1);
            //return 1;

            break;
        default:printf("输入有误，请重新输入！");
	}
}

int passwd_menu()
{
    int select = 0;
    printf("******** 1. 学生登录 **********\n");
    printf("                              \n");
    printf("******** 2. 老师登录 **********\n");
    printf("                              \n");
    printf("******** 3. 管理员登录 ********\n");

    printf("请输入登录人员:(1/2/3): \n");
    scanf("%d", &select);

    return select;
}


int log_on(const char* passwd, int id)
{
    int member_id = 0;
    char member_passwd[10];
    for(int i = 0; i < 3 ;i++) {
        int num = passwd_menu();
        printf("请输入学号/id: \n");
        scanf("%d", &member_id);
        getchar();
        printf("请输入密码: \n");
        fgets(member_passwd, 10, stdin);
        member_passwd[strlen(member_passwd) - 1] = 0;

        if((strcmp(passwd, member_passwd)) || !(id == member_id)) {
            printf("账号或密码输入有误, 请重新输入或退出\n");
            continue;
        }
        printf("登录成功");
        if (num = 3) printf(",管理员\n");
        return 0;
    }
    printf("错误次数过多，系统已锁定！");
    return 1;   //false
}
