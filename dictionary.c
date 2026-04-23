#include <stdio.h>
#include "myheaders.h"
#define Max_words 50
#define Max_word_length 20
#define Max_meaning_length 50


typedef struct {
    char word[Max_word_length]; // 单词
    char meaning[Max_meaning_length]; // 词义
} Word;

Word dictionary[Max_words]; // 词典数组
int wordCount = 0; // 当前词典中的单词数量


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
    scanf("%s", dictionary[wordCount].word);
    
    printf("请输入单词的词义：");
    getchar();//去掉换行符
    fgets(dictionary[wordCount].meaning, Max_meaning_length, stdin);
    wordCount++;
    saveToFile(); // 每次添加新单词后保存到文件
    printf("单词添加成功！\n");
}
 

//浏览单词本
void viewWords() {
     printf("========================================\n");
    if (wordCount == 0) {
        printf("词典为空！\n");
        return;
    }
    printf("当前词典中的单词：\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s: %s", dictionary[i].word, dictionary[i].meaning);
    }
}


/*文件保存到磁盘模块*/
#define FILE_NAME "dic.txt"

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
    if(fileExists("dic.txt")) {
        fp = fopen(FILE_NAME, "ab");
    } else {
        fp = fopen(FILE_NAME, "wb");
    }// 如果文件存在则以追加模式打开，否则以写入模式创建新文件
    

    if (fp == NULL) {
        printf("can't open this file！\n");
        exit(0);
    }
    fwrite(&wordCount, sizeof(int), 1, fp); // 写入词典数量
    fwrite(dictionary, sizeof(Word), wordCount, fp); // 写入词典内容
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
    fread(&wordCount, sizeof(int), 1, file); // 读取词典数量
    fread(dictionary, sizeof(Word), wordCount, file); // 读取词典内容
    fclose(file);
    printf("数据已从文件加载！\n");
}