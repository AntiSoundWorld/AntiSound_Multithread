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


typedef struct LoadingBarData
{
    int numOfWords;
}loadingBarData_t;

typedef struct Info
{
    char* searchWord;
    int numOfThreads;
}info_t;

typedef struct Datas
{
    info_t* info;

    splitter_t* splittedBook;
    word_t* words;
    int numOfIdentyWords;
    char* searchWord;
}datas_t;

splitter_t* splitBook(char* text, int quantityOfParts);

splitter_t* initializeSplitter();

word_t* initializeWords();

loadingBarData_t* initializeLoadingBarData();

char* copyText(FILE* book);

bool isWordsIdentity(char* data, char* word);

void* getNumOfIdentyWords(void* datas);

word_t* splitWords(char* words);

void addData(word_t* structure, char* buffer);

void check(splitter_t* data, char* word);

datas_t* initializedDatas();

void showInfo(void* data);

void* loadingBar();

int getNumOfWords(splitter_t* splittedBook);

void calculatingNumOfWords();

void antiSound_lounchThreads(loadingBarData_t* loadingBarData, datas_t* datas);

info_t* getInfo();