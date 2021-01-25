#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Datas
{
    FILE* book;
    char* word;
}datas_t;

int findWord(FILE* book, char* word);

void* calculateWords(void* datas);

bool isWordExist(char* data, char* word);


char* reset();
