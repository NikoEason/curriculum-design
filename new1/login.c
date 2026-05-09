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
struct user current;
int choice;
int state=0; //登录状态,0表示未登录,1表示已登录
//账户登录函数
void choose(){
    printf("1、登录账户\n");
    printf("2、注册账户\n");
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

    FILE *file = fopen("user.dat", "rb");
    if (file == NULL) {
        printf("无法打开用户文件！\n");
        return;
    }
    struct user u;
    while (fread(&u, sizeof(struct user), 1, file)) {
        if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0) {
            printf("登录成功！\n");
            state=1;
            current=u;
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
    FILE *file = fopen("user.dat", "ab");
    if (file == NULL) {
        printf("无法打开用户文件！\n");
        return;
    }
    struct user u;
    int length = (int)ftell(file);
    int i_d = length / sizeof(struct user) + 1;
    //fseek(file,0,SEEK_SET);
    u.id = i_d;
    u.sco = 0;
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
void savesco(int score){
    //if(state==1)
    current.sco=score;
    FILE *fp=fopen("user.dat","rb");
    fseek(fp, 0, SEEK_END);
    int length = (int)ftell(fp);
    int n=length / sizeof(struct user);
    fseek(fp, 0, SEEK_SET);
    struct user *cur;
    cur=(struct user *)malloc(n*sizeof(struct user));
    int k;
    for(k=0;k<n;k++){
    fread(&cur[k], sizeof(struct user), 1, fp);
        if (current.id==cur[k].id) {
            cur[k].sco=current.sco;
        }
    }
    fclose(fp);
    fp=fopen("user.dat","wb");
    for(k=0;k<n;k++){
    fwrite(&cur[k], sizeof(struct user), 1, fp);
        
    }
    fclose(fp);
    FILE *file = fopen("user.dat", "rb");
    if (file == NULL) {
        printf("无法打开用户文件！\n");
        return;
    }
    struct user u;
    //int *p;
    //p=(int *)malloc(n*sizeof(int));
    struct ranks *r;
    r=(struct ranks *)malloc(n*sizeof(struct ranks));
    int i,j;
    while (fread(&u, sizeof(struct user), 1, file)){
        r[k].id=u.id;
        r[k].sco=u.sco;
        strcpy(r[k].username, u.username);
        k++;
    }
    fclose(file);
    //排序
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(r[j].sco<r[j+1].sco){
                struct ranks temp=r[j];
                r[j]=r[j+1];
                r[j+1]=temp;
            }
        }
    }
    file = fopen("ranking.dat", "wb");//这里用"wb"是因为排行榜每次保存分数后都要更新,也就是要覆写,而非追加
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
    free(cur);
    free(r);
}
void showsco(){
    FILE *file = fopen("ranking.dat", "rb");
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
