#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "myheaders.h"
int main()
{
    int mode;
    if(fileExists("dic.dat")) {
        loadFromFile(); // 启动程序时加载词典数据
    } else {
        printf("文件不存在，无法加载数据！\n");
    }
    
    Showwelcome();
    do{
    Menudisplay();
    scanf("%d",&mode);
    while (getchar() != '\n');

    switch (mode)
    {
    case 1: 
        account(); // 调用登录函数
        break;
    case 2:
        diclayout();
        break;
    case 3:
        checklogin();//检查登陆状态
        // 检查词库是否为空
    if (wordCount == 0) {
        printf("\n词库为空！请先去“词典管理”录入单词！\n");
        return;
    }
    //  选择题目数量
    int questionCount = selectQuestionCount();
    
    //  开始游戏、判断答案、计算得分
    int score = startGame(questionCount);
    savesco(score);//保存分数
        break;
    case 4:
        showsco();//数据存储管理
        break;
    case 5:
        return 0;
    default:
        printf("faulty operation");
        break;
    }

    printf("\n按任意键继续...\n");
    getchar();
    getchar();
    }while(1);

    return 0;
}
