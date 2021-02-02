#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct Words
{
    char* word;
    struct Words* next;
}word_t;

typedef struct Splitter
{
    int page;
    word_t* words;
    struct Splitter* next;
}splitter_t;

typedef struct Datas
{
    char* searchWord;
    word_t* words;
}datas_t;

splitter_t* splitBook(char* text, int quantityOfParts);

splitter_t* initializeSplitter();

word_t* initializeWords();

char* copyText(FILE* book);

bool isWordsIdentity(char* data, char* word);

void* getNumOfIdentyWords(void* datas);

word_t* splitWords(char* words);

void addData(word_t* structure, char* buffer);

void check(splitter_t* data, char* word);

datas_t* initializedDatas();

void showWords(word_t* words);

void info(int numOfIdentyWords);
