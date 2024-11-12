#include <stdio.h>
#include <pthread.h>

/*
 * This function is the code of PThread
 */
void * my_pthread_fn(void* args)
{
    printf("\t\t\t\t\t\t\t\tHello World! I am a SLAVE thread\n");
}

int main()
{

    /*
    
        int pthread_create (pthread_t *ID,
                            pthread_attr_t *attr,
                            void *(*body)(void *),
                            void * arg
 		     );
    */
    pthread_t mythread;
    pthread_attr_t attr;

    int res = pthread_attr_init(&attr);

    printf("Hello World! I am the MASTER thread, before creating slaves\n");
    res = pthread_create (&mythread,                            // ==> FORK
                          &attr,
                          my_pthread_fn,
                          (void *) 0);
    res = pthread_attr_destroy(&attr);
    printf("Hello World! I am the MASTER thread, after creating slaves\n");

    // Here, I can do other stuff

    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");
    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");
    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");
    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");
    printf("Hello World! I am the MASTER thread, and I am doing some stuff...\n");

    /*
        int pthread_join ( pthread_t th,
                           void **thread_return);
    */
    void * returnvalue;
    printf("Hello World! I am the MASTER thread, before joining slaves\n");
    res = pthread_join (mythread, &returnvalue);                // <== JOIN
    printf("Hello World! I am the MASTER thread, after joining slaves\n");
    
    return 0;
}