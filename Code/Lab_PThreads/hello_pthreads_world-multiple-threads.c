#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 16

/*
 * This function is the code of PThread
 */
void * my_pthread_fn(void* args)
{
    // Unbox/unmarshall my (user defined) ID
    int my_id = * (int *) args; // This cast might generate a warning
    
    printf("\t\t\t\t\tHello World! I am a thread %d, and the OS assigned me the ID %lu\n", my_id, pthread_self());

    return NULL;
}

int main()
{
    pthread_t mythread[NUM_THREADS];
    pthread_attr_t attr[NUM_THREADS];
    int res;

    printf("Hello World! I am the MASTER thread, before creating slaves\n");
    for (unsigned int i = 1; i < NUM_THREADS; i++)      // ==> FORK
    {
        res = pthread_attr_init(&attr[i]);
                                                        
        res = pthread_create (&mythread[i],
                              &attr[i],
                              my_pthread_fn,
                              // Define thread Id (user-defined), from 1 onwards,
                              // and pass it as args (boxing/marshalling)
                              (void *) &i // This cast might generate a warning
                             );
        
        if(res != 0)
        {
            printf("ERROR in pthread_create. OS returned %d\n", res);
            return -1;
        }
        res = pthread_attr_destroy(&attr[i]);
    }

    // I also take part into computation, by directly calling the BODY fn
    my_pthread_fn((void *)0); // I am thread #0

    void * returnvalue;
    printf("Hello World! I am the MASTER thread, before joining slaves\n");
    
    for (unsigned int i = 1; i < NUM_THREADS; i++)      // <== JOIN
        res = pthread_join (mythread[i], &returnvalue);

    printf("Hello World! I am the MASTER thread, after joining slaves\n");
    
    return 0;
}