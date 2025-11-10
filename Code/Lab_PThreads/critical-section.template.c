#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void * body(void * arg)
{
    char *mychar = (char *) arg;

    for (int i=0; i<40; i++)
    {
        for (int j=0; j<20; j++)
        {
            printf("%c", *mychar);
        }
        //printf("\n");
    }
}

int main()
{
    pthread_t t1,t2,t3;
    pthread_attr_t myattr;
    int err;

    pthread_attr_init(&myattr);
    err = pthread_create(&t1, &myattr, body, (void *)".");
    err = pthread_create(&t2, &myattr, body, (void *)"#");
    err = pthread_create(&t3, &myattr, body, (void *)"o");
    pthread_attr_destroy(&myattr);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}