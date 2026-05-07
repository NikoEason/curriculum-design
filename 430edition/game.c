#include "stdio.h"
#include "myheaders.h"
#define Max_words 50
#define Max_word_length 20
#define Max_meaning_length 50
#define Max_meanings 5
typedef struct {
    char word[Max_word_length]; // 单词
    char meaning[Max_meanings][Max_meaning_length]; // 多个词义及最大长度
    int meaningCount; // 当前词义数量
} Word;
Word dictionary[Max_words]; // 词典数组
int i,j,wordCount = 0; // 当前词典中的单词数量
#define MAX_USERNAME 20   // 用户名最大长度
#define MAX_RANKING 10    // 排行榜最多显示人数
#define MAX_INPUT 100     // 用户输入最大长度
typedef struct {
    char username[MAX_USERNAME]; // 用户名
    int score;                   // 得分
} Ranking;
Ranking rankingList[MAX_RANKING]; // 排行榜数组
int rankingCount = 0;             // 当前排行榜人数
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
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

// 选择题目数目
int selectQuestionCount() {
    int count;
    printf("\n===== 选择题目数量 =====\n");
    printf("请输入题目数量（1-%d）：", wordCount);
    
    while (1) {
        scanf("%d", &count);
        if (count >= 1 && count <= wordCount) {
            break;
        }
        printf("输入非法！请输入1-%d之间的数字：", wordCount);
    }
    
    return count;
}

// 随机出题并返回得分
int startGame(int questionCount) {
    int score = 0;
    int used[Max_words] = {0}; 
    
    printf("\n===== 开始答题 =====\n");
    printf("规则：根据中文释义输入对应的英文单词\n\n");
    
    srand((unsigned int)time(NULL));
    for (int i = 0; i < questionCount; i++) {
        int index;
        do {
            index = rand() % wordCount;
        } while (used[index] == 1);
        used[index] = 1;
        char userAnswer[MAX_INPUT];
        printf("第%d题：", i+1);
        for (int m = 0; m < dictionary[index].meaningCount; m++) {
            printf("%s", dictionary[index].meaning[m]);
            if (m < dictionary[index].meaningCount - 1) {
                printf(" / ");
            }
        }
        printf("\n你的答案：");
        scanf("%s", userAnswer);
    // 判断答案
        char correctAnswer[20];
        strcpy(correctAnswer, dictionary[index].word);
        toLowerCase(userAnswer);
        toLowerCase(correctAnswer);
        
        if (strcmp(userAnswer, correctAnswer) == 0) {
            printf("✅ 回答正确！\n\n");
            score += 10; // 每题10分
        } else {
            printf("❌ 回答错误！正确答案是：%s\n\n", dictionary[index].word);
        }
    }
    
    // 计算得分
    printf("===== 答题结束 =====\n");
    printf("本次共答%d题，正确%d题，总得分：%d分\n", 
           questionCount, score/10, score);
    
    return score;
}

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

// 游戏模块主入口
void gameModule() {
    // 检查词库是否为空
    if (wordCount == 0) {
        printf("\n词库为空！请先去“词典管理”录入单词！\n");
        return;
    }
    char username[MAX_USERNAME];
    
    //  用户登录
    if (!userLogin(username)) {
        return;
    }
    
    //  选择题目数量
    int questionCount = selectQuestionCount();
    
    //  开始游戏、判断答案、计算得分
    int score = startGame(questionCount);
    
    //  更新排行榜
    updateRanking(username, score);
    
    //  显示排行榜
    showRanking();
}

int main() {
    if (fileExists("dic.dat")) {
        loadFromFile();
    }
    
    int choice;
    while (1) {
        printf("\n========================================\n");
        printf("       英语单词学习系统\n");
        printf("========================================\n");
        printf("1. 词典管理\n");
        printf("2. 单词游戏\n");
        printf("3. 查看排行榜\n");
        printf("0. 退出系统\n");
        printf("========================================\n");
        printf("请输入你的选择：");
        
        scanf("%d", &choice);
        while (getchar() != '\n'); // 清除缓冲区
        
        switch (choice) {
            case 1:
                diclayout(); // 进入你的词典管理菜单
                break;
            case 2:
                gameModule(); // 进入单词游戏
                break;
            case 3:
                showRanking(); // 查看排行榜
                break;
            case 0:
                printf("感谢使用，再见！\n");
                return 0;
            default:
                printf("输入错误，请重新选择！\n");
        }
    }
    return 0;
}