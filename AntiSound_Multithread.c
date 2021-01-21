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
    printf("newThread1 %ld\n", pthread_self());

    pthread_create(&newThread2, NULL, antiSound_multithread_helloWorld, NULL);
    printf("newThread2 %ld\n", pthread_self());
    
    pthread_create(&newThread3, NULL, antiSound_multithread_helloWorld, NULL);
    printf("newThread3 %ld\n", pthread_self());

    pthread_create(&newThread4, NULL, antiSound_multithread_helloWorld, NULL);
    printf("newThread4 %ld\n", pthread_self());

    pthread_join(newThread1, NULL);
    pthread_join(newThread2, NULL);
    pthread_join(newThread3, NULL);
    pthread_join(newThread4, NULL);

    exit(0);
}

void* antiSound_multithread_helloWorld(void* value)
{
    printf("Hello World\n");

    return NULL;
}