#include "stdio.h"
#include "myheaders.h"
struct user {
    int id;
    int sco;
    char username[20];
    char password[20];
};
struct ranks{
    int id;
    char username[20];
    int sco;
};
int choice;
int state=0; //登录状态,0表示未登录,1表示已登录
//账户登录函数
void choose(){
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
    choose();
    break;
}
}
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
            fclose(file);
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
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    int i_d = length / sizeof(struct user) + 1;
    int s0=0;
    //fseek(file,0,SEEK_SET);
    u.id = i_d;
    u.sco = s0;
    strcpy(u.username, username);
    strcpy(u.password, password);
    fwrite(&u, sizeof(struct user), 1, file);
    fclose(file);
    printf("注册成功！\n");
    choose();
}
void account(){
    choose();
}
void checklogin(){
    if(state==1){
        printf("已登录\n");
    }
    while(state==0){
        printf("未登录\n");
        account();
    }
}
void savesco(){
    //if(state==1)
    FILE *file = fopen("user.dat", "r");
    if (file == NULL) {
        printf("无法打开用户文件！\n");
        return;
    }
    struct user u;
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    int n=length / sizeof(struct user);
    fseek(file, 0, SEEK_SET);
    //int *p;
    //p=(int *)malloc(n*sizeof(int));
    struct ranks r[n];
    int k=0;
    int i,j;
    while (fread(&u, sizeof(struct user), 1, file)){
        r[k].id=u.id;
        r[k].sco=u.sco;
        strcpy(r[k].username, u.username);
        k++;
    }
    fclose(file);
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(r[j].sco<r[j+1].sco){
                struct ranks temp=r[j];
                r[j]=r[j+1];
                r[j+1]=temp;
            }
        }
    }
    file = fopen("ranking.dat", "w");//这里用"w"是因为排行榜每次保存分数后都要更新,也就是要覆写,而非追加
    if (file == NULL) {
        printf("无法打开用户文件！\n");
        return;
    }
    if(n<10){
        for(k=0;k<n;k++){
            fwrite(&r[k],sizeof(struct ranks),1,file);
            printf("id=%d\tusername=%s\tscore=%d\t",r[k].id,r[k].username,r[k].sco);
            printf("\n");
        }
    } else{
        for(k=0;k<10;k++){
            fwrite(&r[k],sizeof(struct ranks),1,file);
            printf("id=%d\tusername=%s\tscore=%d\t",r[k].id,r[k].username,r[k].sco);
            printf("\n");
        }
    }
    fclose(file);
}
void showsco(){
    FILE *file = fopen("ranking.dat", "r");
    if (file == NULL) {
        printf("无法打开排行榜文件！\n");
        return;
    }
    struct ranks r;
    printf("排行榜：\n");
    while (fread(&r, sizeof(struct ranks), 1, file)) {
        printf("id=%d\tusername=%s\tscore=%d\t",r.id,r.username,r.sco);
        printf("\n");
    }
    fclose(file);
}
