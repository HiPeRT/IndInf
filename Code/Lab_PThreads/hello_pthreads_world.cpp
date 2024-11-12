#include <iostream>
using namespace std;

#include <pthread.h>

/*
 * This function is the code of PThread
 */
void * my_pthread_fn(void* args)
{
    cout << "\t\t\t\t\t\t\t\tHello World! I am a SLAVE thread" << endl;
    return (void *) 0;
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

    cout << "Hello World! I am the MASTER thread, before creating slaves" << endl;
    res = pthread_create (&mythread,                            // ==> FORK
                          &attr,
                          my_pthread_fn,
                          (void *) 0);
    res = pthread_attr_destroy(&attr);
    cout << "Hello World! I am the MASTER thread, after creating slaves" << endl;

    // Here, I can do other stuff

    cout << "Hello World! I am the MASTER thread, and I am doing some stuff..." << endl;
    cout << "Hello World! I am the MASTER thread, and I am doing some stuff..." << endl;
    cout << "Hello World! I am the MASTER thread, and I am doing some stuff..." << endl;
    cout << "Hello World! I am the MASTER thread, and I am doing some stuff..." << endl;
    cout << "Hello World! I am the MASTER thread, and I am doing some stuff..." << endl;

    /*
        int pthread_join ( pthread_t th,
                           void **thread_return);
    */
    void * returnvalue = new int;
    cout << "Hello World! I am the MASTER thread, before joining slaves" << endl;
    res = pthread_join (mythread, &returnvalue);                // <== JOIN
    cout << "Hello World! I am the MASTER thread, after joining slaves" << endl;
    
    return 0;
}