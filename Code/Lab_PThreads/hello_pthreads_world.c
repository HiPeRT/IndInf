#include <stdio.h>

#include <pthread.h>

/*
 * This function is the code of PThread
 */
void * my_pthread_fn(void* args)
{
    printf("\t\t\t\t\t\t\t\tHello World! I am a SLAVE thread\n");

    //return (void *) 0;
    //...or...
    return NULL;
    /* NOTE: in most OSses and stdlibs, it might be useful to define NULL as:
     * #define NULL (void *)0
     */
}

int main()
{
    printf("Hello World! I am the MASTER thread, before creating slaves\n");
                         
    /*  
        int pthread_create (pthread_t *ID,
                            pthread_attr_t *attr,
                            void *(*body)(void *),
                            void * arg
 		     );
    */
    pthread_t mythread;
    pthread_attr_t attr;

    int res = pthread_attr_init(&attr);                                             // ==> FORK
    res = pthread_create (&mythread,     // OUT param: the assigned thread ID   
                          &attr,         // We won't see this
                          my_pthread_fn, // This is the body of PThread
                          (void *) 0     // ..or NULL... this are the args passed to pthread fn
                         );

    // Checking that the call to pthread-create succeeds.
    // Actually, this should be done for every call to any pthread_* API
    if(res != 0)
    {
        printf("ERROR in pthread_create. OS returned %d\n", res);
        return -1;
    }

    res = pthread_attr_destroy(&attr);

    printf("Hello World! I am the MASTER thread, after creating slaves\n");

    // Here, I can do other stuff

    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");
    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");
    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");
    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");
    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");

    printf("Hello World! I am the MASTER thread, before joining slaves\n");
    /*
        int pthread_join ( pthread_t th,
                           void **thread_return);
    */
    void * returnvalue;
    res = pthread_join (mythread, &returnvalue);                                    // <== JOIN

    printf("Hello World! I am the MASTER thread, after joining slaves\n");
    
    return 0;
}