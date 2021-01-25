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
    
    int i = 1;

    pthread_t threads[16];

    while (i <= namThreads)
    {
        pthread_t thread;

        threads[i] = thread;
        
        pthread_create(&thread, NULL, calculateWords(book, data), NULL);
        pthread_join(threads[i], NULL);
        i++;
    }
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

void* calculateWords(FILE* book, char* word)
{
    printf("%ld\n", pthread_self());

    printf("%d\n", findWord(book, word));
    
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