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

    char* text = copyText(book);

    datas_t* datas = malloc(sizeof(datas_t));
    datas->word = data;
    
    pthread_t thread;

    splitter_t* part = splitText(text, namThreads);
    splitter_t* pointer = part;

    pointer = pointer->next;

    pthread_t threadTimer;
    pthread_create(&threadTimer, NULL, timer, NULL);

    while (pointer != NULL)
    {
        datas->text = pointer->data;

        pthread_create(&thread, NULL, calculateWords, datas);

        pointer = pointer->next;

        pthread_join(thread, NULL);
    }

    pointer = part; 
    while (pointer != NULL)
    {
        splitter_t* removeItem = pointer;

        pointer = pointer->next;
        free(removeItem->data);
        free(removeItem);
    }

    free(datas);
    free(text);
}

int findWord(char* text, char* word)
{

    char* searchWord = calloc(265, sizeof(char));

    int sum = 0;
    int i = 0;

    int j = 0;
    while(text[j] != '\0')
    {
        if(text[j] != ' ' && text[j] != -1 && text[j] != '\n')
        {
            searchWord[i] = text[j];
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

        j++;
    }

    free(searchWord);
    printf("id[%ld]\n", pthread_self());
    printf("sum [%d]\n", sum);

    return sum;
}

void* calculateWords(void* datas)
{

    datas_t* data = datas;
    
    findWord(data->text, data->word);
    
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

char* copyText(FILE* book)
{
    char* buffer = calloc(100000000, sizeof(char));

    char character = '\0';

    int i = 0;

    while(character != EOF)
    {
        character = fgetc(book);
        buffer[i] = character;
        i++;
    }
    
    char* text = calloc(strlen(buffer) + 1, sizeof(char));
    strncpy(text, buffer, strlen(buffer));

    free(buffer);
    return text;
}

splitter_t* splitText(char* text, int quantity)
{
    size_t sizeOftext = strlen(text);

    int sum = sizeOftext / quantity;

    int i = 0;
    int j = 0;

    char* buffer = calloc(sum, sizeof(char));

    splitter_t* part = malloc(sizeof(splitter_t));

    splitter_t* pointer = part;

    while (true)
    {
        if(j == sum)
        {
            pointer->next = malloc(sizeof(splitter_t));

            pointer->next->data = calloc(strlen(buffer) + 1, sizeof(char));
            strncpy(pointer->next->data, buffer, strlen(buffer));

            pointer->next->next = NULL;

            free(buffer);
            buffer = calloc(sum, sizeof(char));

            j = 0;
            
            pointer = pointer->next;
        }
      
        if(text[i] == '\0')
        {
            break;
        }

        buffer[j] = text[i];

        i++;
        j++;
    }
    
    free(buffer);
    return part;
}

void* timer()
{
    int start, end;
    int ms= 0;
    int ns= 0;
    int sec=0 , min=0 , hrs=0;
    start = clock ();

    while (true)
    {
        end = clock ();
        ns= end - start;
        ms = ns / 10;
        if (ms>100)
        {
            sec = sec + 1; 
            ms= ms - 100;
            start= end;
        }
        if (sec > 59)
        {
            min = min+1;
            sec= 0;
        }
        if (min > 59)
        {
            hrs = hrs + 1;
            min=0;
        }
        printf ("%d:%d:%d.%d\n",hrs, min, sec, ms );
    }
}