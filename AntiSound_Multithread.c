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
    int numThreads;
    scanf("%d", &numThreads);

    char* text = copyText(book);

    datas_t* datas = malloc(sizeof(datas_t));
    datas->word = data;
    
    splitter_t* part = splitText(text, numThreads);
    splitter_t* pointer = part;

    pointer = pointer->next;

    //pthread_t threadTimer;
    //pthread_create(&threadTimer, NULL, timer, NULL);

    pthread_t threads[numThreads];
    threads[0] = '\0';

    int i = 0;

    int start = clock();
    while (i != numThreads)
    {
        pthread_t thread;
        threads[i] = thread;

        printf("length %ld\n", strlen(pointer->data));

        datas->text = pointer->data;

        pthread_create(&thread, NULL, calculateWords, datas);

        pointer = pointer->next;
        i++;
    }

    int j = 0;

    while (j != i)
    {
        pthread_join(threads[j], NULL);
        j++;
    }
    int end = clock();

    int timer = end - start;
    printf("timer %d\n", timer);
    
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

    int result = 0;
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
                result = result + 1;
            }
            
            searchWord = reset(searchWord);

            i = 0; 
        }

        j++;
    }

    free(searchWord);
    printf("id[%ld]\n", pthread_self());
    printf("result [%d]\n", result);

    return result;
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
    bool isСoincidenceExist = false;

    if(strcmp(data, word) == 0)
    {
        isСoincidenceExist = true;
    }

    return isСoincidenceExist;
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

    int result = sizeOftext / quantity;

    int i = 0;
    int j = 0;

    char* buffer = calloc(result, sizeof(char));

    splitter_t* part = malloc(sizeof(splitter_t));

    splitter_t* pointer = part;

    while (true)
    {
        if(j == result)
        {
            pointer->next = malloc(sizeof(splitter_t));

            pointer->next->data = calloc(strlen(buffer) + 1, sizeof(char));
            strncpy(pointer->next->data, buffer, strlen(buffer));

            pointer->next->next = NULL;

            free(buffer);
            buffer = calloc(result, sizeof(char));

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