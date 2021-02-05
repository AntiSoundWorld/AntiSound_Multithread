#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "AntiSound_Multithread.h"

void antiSound_lounchThreads(loadingBarData_t* loadingBarData, datas_t* datas)
{
    int numOfThreads = datas->info->numOfThreads;
    
    pthread_t threadOfLoadingBar;

    pthread_create(&threadOfLoadingBar, NULL, loadingBar, loadingBarData);

    splitter_t* pointer = datas->splittedBook;
    
    int i = 0;

    pthread_t threads[numOfThreads];

    sleep(1);    
    while (pointer != NULL)
    {
        datas->words = pointer->words;

        pthread_t thread;
        threads[pointer->page] = thread;

        pthread_create(&thread, NULL, getNumOfIdentyWords, datas);
        //showWords(pointer->words);

        pointer = pointer->next;
        i++;
    }

    pointer = datas->splittedBook;
    while (pointer != NULL)
    {
        pthread_join(threads[pointer->page], NULL);

        pointer = pointer->next;
    }
}