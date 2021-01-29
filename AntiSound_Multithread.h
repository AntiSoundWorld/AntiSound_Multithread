#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Splitter
{
    char* data;
    struct Splitter* next;
}splitter_t;

typedef struct Datas
{
    char* text;
    char* word;
    splitter_t* part;
}datas_t;


int findWord(char* text, char* word);

void* calculateWords(void* datas);

bool isWordExist(char* data, char* word);

char* copyText(FILE* book);

splitter_t* splitText(char* text, int quantity);

char* reset(char* data);

void* timer();
