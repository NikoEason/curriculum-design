#include "stdio.h"
#include "myheaders.h"
struct user {
    char username[20];
    char password[20];
};
int choice;
int state=0; //登录状态，0表示未登录，1表示已登录
//账户登录函数
void login() {
    char username[20];
    char password[20];

    printf("请输入用户名：");
    scanf("%s", username);
    printf("请输入密码：");
    scanf("%s", password);

    FILE *file = fopen("user.dat", "r");
    if (file == NULL) {
        printf("无法打开用户文件！\n");
        return;
    }
    struct user u;
    while (fread(&u, sizeof(struct user), 1, file)) {
        if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0) {
            printf("登录成功！\n");
            state=1;
            return;
        }
    }
    printf("用户名或密码错误！\n");
    fclose(file);
    state=0;
}
//账户注册界面
void regis() {
    char username[20];
    char password[20];

    printf("请输入用户名：");
    scanf("%s", username);
    printf("请输入密码：");
    scanf("%s", password);

    FILE *file = fopen("user.dat", "a");
    if (file == NULL) {
        printf("无法打开用户文件！\n");
        return;
    }
    struct user u;
    strcpy(u.username, username);
    strcpy(u.password, password);
    fwrite(&u, sizeof(struct user), 1, file);
    fclose(file);
    printf("注册成功！\n");
    printf("按1登录账户\n");
    printf("按2注册账户\n");
    scanf("%d",&choice);
switch(choice){
case 1:
    login();
    break;
case 2:
    regis();
    break;
}
}
//账户登录注册界面
void account(){
    printf("按1登录账户\n");
    printf("按2注册账户\n");
    scanf("%d",&choice);
switch (choice)
{
case 1:
    login();
    break;
case 2:
    regis();
    break;
default:
    break;
}
}
void checklogin(){
    if(state==1){
        printf("已登录\n");
    }else{
        printf("未登录\n");
        account();
    }
}

