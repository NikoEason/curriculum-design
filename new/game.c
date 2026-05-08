#include "myheaders.h"
#include <time.h>
#define MAX_USERNAME 20   // 用户名最大长度
#define MAX_RANKING 10    // 排行榜最多显示人数
#define MAX_INPUT 100     // 用户输入最大长度
typedef struct {
    char username[MAX_USERNAME]; // 用户名
    int score;                   // 得分
} Ranking;
Ranking rankingList[MAX_RANKING]; // 排行榜数组
int rankingCount = 0;             // 当前排行榜人数
int i,m;


/*这一段代码跟王重复了，选择性删减
// 用户登录
int userLogin(char *username) {
    printf("\n===== 用户登录 =====\n");
    printf("请输入用户名：");
    scanf("%s", username);
    
// 登录验证
    if (strlen(username) == 0 || strlen(username) >= MAX_USERNAME) {
        printf("用户名长度非法！\n");
        return 0;
    }
    
    printf("登录成功！欢迎你，%s\n", username);
    return 1;
}
*/
//切换英文大小写
void toLowerCase(char *str) {
    for (i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
    }
}
// 选择题目数目
int selectQuestionCount() 
{
    int count;
    printf("\n===== 选择题目数量 =====\n");
    printf("请输入题目数量（1-%d）：", wordCount);
    
    while (1) 
    {
        scanf("%d", &count);
        if (count >= 1 && count <= wordCount) 
        {
            break;
        }
        else 
        {
        printf("输入非法！请输入1-%d之间的数字：", wordCount);
        }
    
        return count;
    }
}

// 随机出题并返回得分
int startGame(int questionCount) {
    
    int score = 0;
    char answer[MAX_INPUT];
    
    printf("\n===== 开始答题 =====\n");
    printf("规则：根据中文释义输入对应的英文单词\n\n");
    
    srand((unsigned int)time(NULL));
    for (i = 0; i <questionCount ; i++) {
        int idx = rand() % wordCount; // 随机选一个单词

        // 随机决定显示英文还是中文
        int showEnglish = rand() % 2;//中英题随机

        if (showEnglish) {
            printf("请翻译：%s\n", dictionary[idx].word);
            printf("你的答案：");
            scanf("%s", answer);

           // 比较答案
            int correct = 0;
            for (m=0; m < dictionary[idx].meaningCount; m++) {
                if (strcmp(answer, dictionary[idx].meaning[m]) == 0) { // 中文直接比较
                    correct = 1;
                    break;
                }
            }
            if (correct) {
                printf("答对了！\n");
                score++;
            } else {
                printf("答错了，正确答案是：%s\n", dictionary[idx].meaning[0]);
                for (m=0; m < dictionary[idx].meaningCount; m++) {
                    printf("%s", dictionary[idx].meaning[m]);
                    if (m < dictionary[idx].meaningCount - 1) printf("; ");
                }
                printf("\n");
            }
            
        } 

        //回答英文
        else {
            printf("请翻译：%s\n", dictionary[idx].meaning[0]);
            printf("你的答案：");
            scanf("%s", answer);

            char answerLower[MAX_INPUT];
            strcpy(answerLower, answer);
            toLowerCase(answerLower);

            char wordLower[Max_word_length];
            strcpy(wordLower, dictionary[idx].word);
            toLowerCase(wordLower);

            if (strcmp(answerLower, wordLower) == 0) {
                printf("答对了！\n");
                score++;
            } else {
                printf("答错了，正确答案是：%s\n", dictionary[idx].word);
            }
        }
    }
    
    // 计算得分
    printf("===== 答题结束 =====\n");
    printf("本次共答%d题，正确%d题，总得分：%d分\n", questionCount, score/10, score);
    return score;
}
void gameModule() {
    
    // 检查词库是否为空
    if (wordCount == 0) {
        printf("\n词库为空！请先去“词典管理”录入单词！\n");
        return;
    }
    //  选择题目数量
    int questionCount = selectQuestionCount();
    
    //  开始游戏、判断答案、计算得分
    int score = startGame(questionCount);
    /*
    //  更新排行榜
    updateRanking(username, score);
    
    //  显示排行榜s
    showRanking();
    */
}
/*
//  更新排行榜
void updateRanking(const char *username, int score) {
    if (rankingCount < MAX_RANKING) {
        strcpy(rankingList[rankingCount].username, username);
        rankingList[rankingCount].score = score;
        rankingCount++;
    } 
    else {
        int minIndex = 0;
        for (int i = 1; i < MAX_RANKING; i++) {
            if (rankingList[i].score < rankingList[minIndex].score) {
                minIndex = i;
            }
        }
        if (score > rankingList[minIndex].score) {
            strcpy(rankingList[minIndex].username, username);
            rankingList[minIndex].score = score;
        }
    }
    
    for (int i = 0; i < rankingCount-1; i++) {
        for (int j = 0; j < rankingCount-i-1; j++) {
            if (rankingList[j].score < rankingList[j+1].score) {
                Ranking temp = rankingList[j];
                rankingList[j] = rankingList[j+1];
                rankingList[j+1] = temp;
            }
        }
    } 
}
/*
// 显示排行榜
void showRanking() {
    printf("\n===== 排行榜 =====\n");
    if (rankingCount == 0) {
        printf("暂无排行数据\n");
        return;
    }
    
    printf("排名\t用户名\t\t得分\n");
    printf("------------------------\n");
    for (int i = 0; i < rankingCount; i++) {
        printf("%d\t%s\t\t%d\n", i+1, rankingList[i].username, rankingList[i].score);
    }
}
 /*
void saveRankingToFile() {
    FILE *fp = fopen("ranking.dat", "wb");
    if (fp == NULL) return;
    fwrite(&rankingCount, sizeof(int), 1, fp);
    fwrite(rankingList, sizeof(Ranking), rankingCount, fp);
    fclose(fp);
}
void loadRankingFromFile() {
    FILE *file = fopen("ranking.dat", "rb");
    if (file == NULL) return;
    fread(&rankingCount, sizeof(int), 1, file);
    fread(rankingList, sizeof(Ranking), rankingCount, file);
    fclose(file);
}*/
// 游戏模块主入口

