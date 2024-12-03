#include <stdio.h>
#include <pthread.h>

#include "CircularArray.h"

static int NUM_THREADS = 4;

// TODO as an exercise, you might want to marshal it in PThread body args
struct CircularArray_t ca;


void * consumer_fn(void * args)
{
    int myid = (int) args;

    printf("Hello, I am consumer thread #%d, and I am extracting an element from the CA\n", myid);

    int num;
    
    extract_CA (&ca, &num);

    printf("[Thread %d] I extracted %d\n", myid, num);

    return NULL;
}

void * producer_fn(void * args)
{
    printf("Hello, I am producer thread\n");

    for(int i=1; i<NUM_THREADS; i++)
        insert_CA (&ca, 100 + i);

    return NULL;
}


int main()
{
    pthread_t mythreads[NUM_THREADS];
    pthread_attr_t myattr;
    int err;
    void *returnvalue;

    err = init_CA (&ca);
    if(err != 0)
    {
        printf("ERROR. CA initialization failed. Exiting...\n");
        return -1;
    }

    for(int i=1; i<NUM_THREADS; i++)
    {
        pthread_attr_init(&myattr);
        err = pthread_create (&mythreads[i], &myattr, consumer_fn, (void *) i);
        pthread_attr_destroy(&myattr);

        if(err != 0)
        {
            printf("ERROR. PThreads creation failed. Exiting...\n");
            return -2;
        }
    }

    producer_fn(NULL);

    for(int i=1; i<NUM_THREADS; i++)
    {
        pthread_join(mythreads[i], &returnvalue);
        
        if(err != 0)
        {
            printf("ERROR. PThreads join failed. Exiting...\n");
            return -3;
        }
    }

    return 0;
}