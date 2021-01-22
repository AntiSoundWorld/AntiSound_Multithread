#include "AntiSound_Multithread.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pthread_t newThread1;
    pthread_t newThread2;
    pthread_t newThread3;
    pthread_t newThread4;

    pthread_create(&newThread1, NULL, antiSound_multithread_helloWorld, NULL);

    pthread_create(&newThread2, NULL, antiSound_multithread_helloWorld, NULL);
    
    pthread_create(&newThread3, NULL, antiSound_multithread_helloWorld, NULL);

    pthread_create(&newThread4, NULL, antiSound_multithread_helloWorld, NULL);

    pthread_join(newThread1, NULL);
    pthread_join(newThread2, NULL);
    pthread_join(newThread3, NULL);
    pthread_join(newThread4, NULL);

    exit(0);
}

void* antiSound_multithread_helloWorld(void* value)
{
    printf("newThread %ld\n\n", pthread_self());
    printf("Hello World\n");

    return NULL;
}