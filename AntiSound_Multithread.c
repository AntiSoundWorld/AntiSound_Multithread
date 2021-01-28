#include "AntiSound_Multithread.h"

#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE* book = fopen("War and Peace.txt", "rt");
    
    if(book == NULL)
    {
        printf("NULL\n");
    }

    char data[80] = "\0";
    printf("insert a word\n");
    scanf("%s", data);

    printf("insert num of threads\n");
    int namThreads;
    scanf("%d", &namThreads);
    
    datas_t* datas = malloc(sizeof(datas_t));
    datas->word = data;
    datas->book = book;
    
    int i = 0;
    
    pthread_t thread;

    while (i != namThreads)
    {
        pthread_create(&thread, NULL, calculateWords, datas);
        i++;
    }

    pthread_join(thread, NULL);
}

int findWord(FILE* book, char* word)
{
    char buffer = '\0';

    char* searchWord = calloc(265, sizeof(char));

    int sum = 0;
    int i = 0;

    while(buffer != EOF)
    {
        buffer = fgetc(book);

        if(buffer != ' ' && buffer != -1 && buffer != '\n')
        {
            searchWord[i] = buffer;
            i++;
        }
        else
        {
            if(isWordExist(searchWord, word))
            {
                sum = sum + 1;
            }
            
            searchWord = reset(searchWord);

            i = 0; 
        }
    }

    return sum;
}

void* calculateWords(void* datas)
{
    printf("id[%ld]\n", pthread_self());

    datas_t* data = datas;

    printf("num - %d\n\n", findWord(data->book, data->word));
    
    return NULL;
}

char* reset(char* data)
{
    free(data);
    return data = calloc(265, sizeof(char));
}

bool isWordExist(char* data, char* word)
{
    bool isWordExist = false;

    if(strcmp(data, word) == 0)
    {
        isWordExist = true;
    }

    return isWordExist;
}