#include <iostream>
using namespace std;

#include <pthread.h>

/*
 * This function is the code of PThread
 */
void * my_pthread_fn(void* args)
{
    // args contains the address of MYVAR

    int *myvar_ptr = (int *) args; // Cast to the appropriate type
    int myvar_value = *myvar_ptr;   // Dereference to get the value

    cout << "\t\t\t\t\t\t\t\tMYVAL has address " << myvar_ptr << endl;
    cout << "\t\t\t\t\t\t\t\tMYVAL has value " << myvar_value << endl;
    //cout << "\t\t\t\t\t\t\t\tMYVAL has value " << *myvar_ptr << endl; // This is the same
    //cout << "\t\t\t\t\t\t\t\tMYVAL has value " << *args << endl; // This won't work

    *myvar_ptr = 5;

    cout << "\t\t\t\t\t\t\t\tNow MYVAL has value " << *myvar_ptr << endl;

    return NULL;
}

int main()
{
    pthread_t mythread;
    pthread_attr_t attr;

    int myvar = 11;

    cout << "MYVAR has address " << &myvar << " and value " << myvar << endl;

    int res = pthread_attr_init(&attr);

    res = pthread_create (&mythread,     // OUT param: the assigned thread ID   
                          &attr,         // We won't see this
                          my_pthread_fn, // This is the body of PThread
                          (void *) &myvar// ..or NULL... this are the args passed to pthread fn
                         );
	
	// In this region here (aka: PARALLEL region), the status of the program is not defined
    // (but I exploit parallelism)
    
    res = pthread_attr_destroy(&attr);
    void * returnvalue = new int;
    res = pthread_join (mythread, &returnvalue);

    cout << "MYVAR now is " << myvar << endl;
    
    return 0;
}