#ifndef DICTIONARY_H
#define DICTIONARY_H

#define Max_words 50
#define Max_word_length 20
#define Max_meaning_length 50
#define Max_meanings 5

typedef struct {
    char word[Max_word_length]; // 单词
    char meaning[Max_meanings][Max_meaning_length]; // 多个词义及最大长度
    int meaningCount; // 当前词义数量
} Word;
extern Word dictionary[Max_words]; // 词典数组
extern int wordCount;


void diclayout();
void addWord();
void viewWords();
void lookupWord();
void saveToFile();
void updateFile();
void loadFromFile();
void addmeaning();
void modifymeaning();
void deleteWord();
int fileExists(const char *filename);

#endif