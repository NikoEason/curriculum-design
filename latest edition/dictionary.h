#ifndef DICTIONARY_H
#define DICTIONARY_H

void diclayout();
void addWord();
void viewWords();
void lookupWord();
void saveToFile();
void loadFromFile();
void addmeaning();
void modifymeaning();
void deleteWord();
int fileExists(const char *filename);

#endif