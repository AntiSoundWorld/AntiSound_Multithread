#include "AntiSound_Multithread.h"

#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static int numofFoundedWords = 0;
pthread_t threadOfLoadingBar;

int main()
{
    FILE* book = fopen("War and Peace.txt", "rt");

    if(book == NULL)
    {
        printf("NULL\n");
    }

    char searchWord[80] = "\0";
    printf("insert a word\n");
    scanf("%s", searchWord);
    
    printf("insert num of threads\n");
    int numThreads;
    scanf("%d", &numThreads);

    datas_t* datas = initializedDatas();
    datas->searchWord = searchWord;

    splitter_t* splittedBook = splitBook(copyText(book), numThreads);
    printf("Finish split book\n");

    splitter_t* pointer = splittedBook;

    datas->splittedBook = splittedBook;

    loadingBarData_t* loadingBarData = initializeLoadingBarData();

    loadingBarData->numOfWords = getNumOfWords(splittedBook);

    pthread_create(&threadOfLoadingBar, NULL, loadingBar, loadingBarData);

    pthread_t threads[numThreads];

    int i = 0;
    int start = clock();
    while (pointer != NULL)
    {
        datas->words = pointer->words;

        pthread_t thread;
        threads[pointer->page] = thread;

        pthread_create(&thread, NULL, getNumOfIdentyWords, datas);
        printf("\npage[%d]\n\n", pointer->page);
        //showWords(pointer->words);

        pointer = pointer->next;
        i++;
    }

    pointer = splittedBook;
    while (pointer != NULL)
    {
        pthread_join(threads[pointer->page], NULL);
       
        pointer = pointer->next;
    }

    pthread_join(threadOfLoadingBar, NULL);


    int end = clock();
    int time = end - start;

    printf("time:[%d]\n", time);
    sleep(1);
}

char* copyText(FILE* book)
{
    fseek(book, 0L, SEEK_END);
    long int length = ftell(book); 
    fseek(book, 0L, SEEK_SET);

    char* text = calloc(length + 1, sizeof(char));
    
    char buffer;

    int i = 0;
    while (buffer != EOF)
    {
        buffer = fgetc(book);
        text[i] = buffer;
        i++;
    }
    
    //fgets(text, length, book);
    
    return text;
}

splitter_t* splitBook(char* text, int quantityOfParts)
{
    splitter_t* parts = initializeSplitter();
    splitter_t* pointer = parts;

    size_t sizeOfText = strlen(text);

    int result = sizeOfText / quantityOfParts;
    
    int point = 0;
    
    int id = 0;

    int j = 0;

    while (j != quantityOfParts)
    {
        if(point + result <= sizeOfText)
        {
            point = point + result;
        }
        else
        {
            point = sizeOfText;
        }

        while (true)
        {
            if(text[point] == ' ' || text[point] == ',' || text[point] == '.' || text[point] == '\0' || text[point] == '\n')
            {
                break;
            }

            point++;
        }

        char* newPart = calloc(id + point + 1, sizeof(char));

        int i = 0;
        while (id != point)
        {
            newPart[i] = text[id];
            i++;
            id++;
        }

        if(pointer->words == NULL)
        {
            pointer->page = 0;
            pointer->words = splitWords(newPart);
            pointer->next = NULL;
        }
        else
        {
            pointer->next = initializeSplitter();

            pointer->next->page = pointer->page + 1;
            pointer->next->words = splitWords(newPart);
            pointer->next->next = NULL;

            pointer = pointer->next;

        }

        j++;
    }
    
    return parts;
}

splitter_t* initializeSplitter()
{
    splitter_t* splitter = malloc(sizeof(splitter_t));
    splitter->page = -1;
    splitter->words = NULL;
    splitter->next = NULL;

    return splitter;
}

word_t* initializeWords()
{
    word_t* datas = malloc(sizeof(word_t));
    datas->word = NULL;
    datas->next = NULL;

    return datas;
}

bool isWordsIdentity(char* data, char* word)
{
    bool isWordIdentity = false;

    if(strcmp(data, word) == 0)
    {
        isWordIdentity = true;
    }

    return isWordIdentity;
}

void* getNumOfIdentyWords(void* datas)
{
    int numOfIdentyWords = 0;

    datas_t* pointer = datas;
    word_t* pointerWords = pointer->words;


    while (pointerWords != NULL)
    {
        if(strcmp(pointerWords->word, pointer->searchWord) == 0)
        {
            numOfIdentyWords = numOfIdentyWords + 1;
        }

        numofFoundedWords = numofFoundedWords + 1;

        pointerWords = pointerWords->next;
    }


    info(numOfIdentyWords);

    return NULL;
}


word_t* splitWords(char* words)
{
    size_t sizeOfWords = strlen(words);

    word_t* word = initializeWords();

    char buffer[100] = "";

    int i = 0;
    int j = 0;

    if(words[0] == ' ')
    {
        i++;
    }

    while (i <= sizeOfWords)
    {
        //printf("%c", words[i]);
        if(words[i] != ' ' && words[i] != '.' && words[i] != ',' && words[i] != '\n')
        {
            buffer[j] = words[i];
            j++;
        }

        if(words[i] == ' ' || words[i] == '\0')
        {
            addData(word, buffer);

            memset(buffer, 0, strlen(buffer));

            j = 0;
        }

        i++;
    }

    return word;
}


int getNumOfWords(splitter_t* splittedBook)
{
    int numWords = 0;
    splitter_t* pointerSplittedBook = splittedBook;

    while(pointerSplittedBook != NULL)
    {
        word_t* pointerWords = pointerSplittedBook->words;
        while (pointerWords != NULL)
        {
            numWords = numWords + 1;
            pointerWords = pointerWords->next;
        }

        pointerSplittedBook = pointerSplittedBook->next;
    }

    return numWords;
}


void addData(word_t* structure, char* buffer)
{  
    word_t* pointer = structure;
    
    while (pointer->next != NULL)
    {
        pointer = pointer->next;
    }
    
    if(pointer->word == NULL)
    {
        pointer->word = calloc(strlen(buffer) + 1, sizeof(char));
        strncpy(pointer->word, buffer, strlen(buffer));
    }
    else
    {
        pointer->next = initializeWords();
        pointer->next->word = calloc(strlen(buffer) + 1, sizeof(char));
        strncpy(pointer->next->word, buffer, strlen(buffer));
        pointer->next->next = NULL;
    }
}

loadingBarData_t* initializeLoadingBarData()
{
    loadingBarData_t* loadingBar = malloc(sizeof(loadingBarData_t));
    loadingBar->numOfWords = -1;

    return loadingBar;
}

datas_t* initializedDatas()
{
    datas_t* datas = malloc(sizeof(datas_t));
    datas->searchWord = NULL;
    datas->words = NULL;

    return datas;
}

void showWords(word_t* words)
{
    word_t* pointer = words;

    while(pointer != NULL)
    {
        printf("word = %s\n", pointer->word);
        pointer = pointer->next;
    }

}

pthread_mutex_t mutex;

void info(int numOfIdentyWords)
{
    pthread_mutex_lock(&mutex);
    printf("\ntread id[%ld]\n", pthread_self());
    printf("numOfIdentyWords [%d]\n", numOfIdentyWords);
    printf("----------------------------------------\n");
    pthread_mutex_unlock(&mutex);
}

void* loadingBar(int numOfWords)
{
    int ten = numOfWords / 10;

    int twenty = ten + ten;
    int thirty = ten + twenty;
    int fourty = ten + thirty;
    int fifty = ten + fourty;
    int sixty = ten + fifty;
    int seventy = ten + sixty;
    int eighty = ten + seventy;
    int ninty = ten + eighty;
    int houndred = numOfWords;

    while (true)
    {
        if(numofFoundedWords ==  ten)
        {
            printf("10");
            fflush(stdout);
        }

        if(numofFoundedWords == twenty)
        {
            printf("20");
            fflush(stdout);
        }

        if(numofFoundedWords == thirty)
        {
            printf("30");
            fflush(stdout);
        }

        if(numofFoundedWords == fourty)
        {
            printf("40");
            fflush(stdout);
        }

        if(numofFoundedWords == fifty)
        {
            printf("50");
            fflush(stdout);
        }

        if(numofFoundedWords == sixty)
        {
            printf("60");
            fflush(stdout);
        }

        if(numofFoundedWords == seventy)
        {
            printf("70");
            fflush(stdout);
        }

        if(numofFoundedWords == eighty)
        {
            printf("80");
            fflush(stdout);
        }

        if(numofFoundedWords == ninty)
        {
            printf("90");
            fflush(stdout);
        }

        if(numofFoundedWords == houndred)
        {
            printf("100");
            fflush(stdout);
            break;
        }
        
    }

    return NULL;
}