#include "AntiSound_Multithread.h"

#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
    FILE* book = fopen("Test.txt", "rt");

    if(book == NULL)
    {
        printf("NULL\n");
    }

    //char data[80] = "\0";
    //printf("insert a word\n");
    //scanf("%s", data);
    printf("insert num of threads\n");
    int numThreads;
    scanf("%d", &numThreads);

    //copyText(book);
    splitBook(book, numThreads);
}

char* copyText(FILE* book)
{
    fseek(book, 0L, SEEK_END);
    long int length = ftell(book); 
    fseek(book, 0L, SEEK_SET);

    char* text = calloc(length + 1, sizeof(char));
    fgets(text, length, book);
    
    printf("%s\n", text);
    
    return text;
}

splitter_t* splitBook(FILE* book, int quantityOfParts)
{
    splitter_t* parts = initializeSplitter();

    fseek(book, 0L, SEEK_END);
    long int length = ftell(book); 
    fseek(book, 0L, SEEK_SET);

    int remainder = length / quantityOfParts;

    splitter_t* pointer = parts;

    int i = 0;

    while (i != remainder)
    {
        char* partOfBook = calloc(remainder + 1, sizeof(char));

        fgets(partOfBook, remainder, book);

        if(parts->data == NULL)
        {
            parts->data = partOfBook;
        }
        else
        {
            pointer->next = initializeSplitter();
            pointer->next->data = partOfBook;
            pointer->next->next = NULL;
            pointer = pointer->next;
        }

        i++;
        printf("%s\n", pointer->data);
    }
    
    return parts;
}
splitter_t* initializeSplitter()
{
    splitter_t* splitter = malloc(sizeof(splitter_t));
    splitter->data = NULL;
    splitter->next = NULL;

    return splitter;
}

datas_t* initializeDatas()
{
    datas_t* datas = malloc(sizeof(datas_t));
    datas->part = NULL;
    datas->text = NULL;
    datas->word = NULL;

    return datas;
}

