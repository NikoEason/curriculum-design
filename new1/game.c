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
            getchar(); // 清除输入缓冲区的换行符

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
            getchar(); // 清除输入缓冲区的换行符

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
    savesco(score);//保存分数
}


