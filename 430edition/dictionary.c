#include <stdio.h>
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


//词典布局
void diclayout()
{
    int choice;
    do{
    printf("========================================\n");
    printf("1、录入新单词\n");
    printf("2、浏览单词本\n");
    printf("3、查找词汇\n");
    printf("4、修改单词\n");
    printf("5、删除单词\n");
    printf("6、返回上一级菜单\n");
    printf("========================================\n");
    printf("请输入你的选择：");

    scanf("%d",&choice);
    while (getchar() != '\n');

    switch (choice)
    {
    case 1:
        addWord();
        break;
    case 2:
        viewWords();
        break;
    case 3:
        lookupWord();
        break;
    case 4:
        printf("1、增添词义\n");
        printf("2、修改词义\n");
        int subChoice;
        scanf("%d", &subChoice);
        while (getchar() != '\n');
        switch (subChoice) {
            case 1:
                addmeaning();
                break;
            case 2:
                modifymeaning();
                break;
            default:
                printf("wrong operation!");
                getchar();
        }
        break;
    case 5:
        deleteWord();
        break;
    case 6:return;
    default:
        printf("wrong operation!");
        getchar();
    }
    }while(1);
}


//添加新单词
void addWord() {
    if (wordCount >= Max_words) {
        printf("词典已满，无法添加新单词！\n");
        return;
    }
    printf("========================================\n");
    printf("请输入新单词：");
    char newWord[Max_word_length];
    scanf("%s", newWord);

    //判断新录入单词是否已存在
    if(wordCount > 0) {
        for (i = 0; i < wordCount; i++) {
            if (strcmp(dictionary[i].word, newWord) == 0) {
                printf("单词已存在！请勿重复添加\n");
                return;
            }
        }
    }
    
    strcpy(dictionary[wordCount].word, newWord);
    printf("请输入单词的词义（最多输入%d个）：", Max_meanings);
    getchar();//去掉换行符

   i = 0;
    while (i < Max_meanings) {
        printf("请输入词义 %d: ", i + 1);
        fgets(dictionary[wordCount].meaning[i], Max_meaning_length, stdin);
        dictionary[wordCount].meaning[i][strcspn(dictionary[wordCount].meaning[i], "\n")] = '\0';  // 去掉换行符
        if (strlen(dictionary[wordCount].meaning[i]) == 0) {
            break;  // 输入空行则结束
        }
        i++;
    }

    dictionary[wordCount].meaningCount = i;  // 设置词义数量
    wordCount++;
    printf("单词添加成功！\n");
    saveToFile();  // 保存到文件
}
//浏览单词本
void viewWords() {
    printf("========================================\n");
    if (wordCount == 0) {
        printf("词典为空！\n");
        return;
    }
    printf("当前词典中的单词：\n");
     for (i = 0; i < wordCount; i++) {
        printf("%s: ", dictionary[i].word);
        for (j = 0; j < dictionary[i].meaningCount; j++) {
            printf("%s", dictionary[i].meaning[j]);
            if (j < dictionary[i].meaningCount - 1) {
                printf("; ");
            }
        }
        printf("\n");
    }
}
//查找词汇
void lookupWord() {
    char searchWord[Max_word_length];
    printf("请输入要查找的单词：");
    scanf("%s", searchWord);
    getchar();
    for (i = 0; i < wordCount; i++) {
        if (strcmp(dictionary[i].word, searchWord) == 0) {
            printf("单词：%s\n", dictionary[i].word);
            printf("词义:");
            for(j = 0; j < dictionary[i].meaningCount; j++) {
                printf(" %s;",dictionary[i].meaning[j]);
            }
            printf("\n");
            return;
        }
    }
    printf("未找到该单词！\n");
}
//增添词义
void addmeaning() {
    char searchWord[Max_word_length];
    printf("请输入要添加词义的单词：");
    scanf("%s", searchWord);
    
    for (i = 0; i < wordCount; i++) {
        if (strcmp(dictionary[i].word, searchWord) == 0) 
        {
            printf("当前词义:");
             for (j =0; j < dictionary[i].meaningCount; j++) 
            {
                printf(" %s;", dictionary[i].meaning[j]);
            }
            printf("\n");
            getchar(); // 清除输入缓冲区中的换行符  
            char newMeaning[Max_meaning_length];
            printf("\n请输入新的词义：");
            fgets(newMeaning, Max_meaning_length, stdin);
            newMeaning[strcspn(newMeaning, "\n")] = '\0';  // 去掉换行符

           // 将新词义添加到原有词义后
            if (dictionary[i].meaningCount < Max_meanings) {
                // 用分号隔开原有词义和新词义
                if (strlen(dictionary[i].meaning[dictionary[i].meaningCount - 1]) > 0) {
                    strcat(dictionary[i].meaning[dictionary[i].meaningCount - 1], "; ");
                }
                strcat(dictionary[i].meaning[dictionary[i].meaningCount - 1], newMeaning);
                dictionary[i].meaningCount++;

                saveToFile();  // 保存更新后的词典
                printf("词义添加成功！\n");
                return;
            }else {
                printf("词义已达最大数量，无法添加新词义！\n");
                return;
            }
        }
    }
    printf("未找到该单词！\n");
}
//修改词义
void modifymeaning() {
    char searchWord[Max_word_length];
    printf("请输入要修改词义的单词：");
    scanf("%s", searchWord);

    // 查找单词
    for (i = 0; i < wordCount; i++) {
        if (strcmp(dictionary[i].word, searchWord) == 0) {
            printf("当前单词为: %s\n", dictionary[i].word);
            
            // 显示已有的词义
            for (j = 0; j < dictionary[i].meaningCount; j++) {
                printf("词义 %d: %s\n", j + 1, dictionary[i].meaning[j]);
            }

            printf("请输入新的词义（若要替换词义，输入对应的数字）：\n");
            int choice;
            printf("请选择要修改的词义编号：");
            scanf("%d", &choice);
            getchar();  // 清除换行符

            if (choice < 1 || choice > dictionary[i].meaningCount) {
                printf("无效的词义编号！\n");
                return;
            }

            // 获取新的词义并替换
            char newMeaning[Max_meaning_length];
             printf("当前词义为: %s\n", dictionary[i].meaning[choice - 1]);
            printf("请输入新的词义：");
            fgets(newMeaning, Max_meaning_length, stdin);
            newMeaning[strcspn(newMeaning, "\n")] = '\0';  // 移除换行符

            // 替换词义
            strcpy(dictionary[i].meaning[choice - 1], newMeaning);

            saveToFile();  // 保存修改后的词典
            printf("词义修改成功！\n");
            return;
        }
    }

    printf("未找到该单词！\n");
}
void deleteWord() {
    char searchWord[Max_word_length];
    printf("请输入要删除的单词：");
    scanf("%s", searchWord);

    for (i = 0; i < wordCount; i++) {
        if (strcmp(dictionary[i].word, searchWord) == 0) {
            // 将后续单词前移覆盖当前单词
            for (j = i; j < wordCount - 1; j++) {
                dictionary[j] = dictionary[j + 1];
            }
            wordCount--; // 减少单词数量
            saveToFile(); // 保存更新后的词典
            printf("单词删除成功！\n");
            return;
        }
    }
    printf("未找到该单词！\n");
}


/*文件保存到磁盘模块*/
#define FILE_NAME "dic.dat"
// 判断文件是否存在
int fileExists(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file) {
        fclose(file);
        return 1; // 文件存在
    }
    return 0; // 文件不存在
}

// 将词典保存到文件
void saveToFile() {
   FILE *fp;
    if(fileExists("dic.dat")) {
        fp = fopen(FILE_NAME, "ab");
    } else {
        fp = fopen(FILE_NAME, "wb");
    }// 如果文件存在则以追加模式打开，否则以写入模式创建新文件
    

    if (fp == NULL) {
        printf("can't open this file！\n");
        exit(0);
    }

    fwrite(&dictionary[wordCount-1], sizeof(Word), 1, fp); // 写入单词数据
    fclose(fp); 
    printf("数据已保存到文件！\n");
}

// 从文件加载词典
void loadFromFile() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("文件不存在，加载数据失败！\n");
        exit(0);
    }
    while(fread(&dictionary[wordCount], sizeof(Word), 1, file) == 1) {
        wordCount++;
        if (wordCount >= Max_words) {
            printf("词典已满，无法加载更多数据！\n");
            break;
        }
    }
    fclose(file);
    printf("数据已从文件加载！\n");
}
