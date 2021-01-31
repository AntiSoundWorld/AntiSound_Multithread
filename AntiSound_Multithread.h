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


splitter_t* splitBook(FILE* book, int quantityOfParts);

splitter_t* initializeSplitter();

datas_t* initializeDatas();

