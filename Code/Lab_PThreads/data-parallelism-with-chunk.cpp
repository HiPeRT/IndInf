#include <iostream>
using namespace std;

#include <pthread.h>

#define NUM_THREADS 16
#define SIZE 8

typedef struct data_s
{
    int *arr_ptr;
    int myid;
} data_t;

/*
 * This function is the code of PThread
 */
void * my_pthread_fn(void* args)
{
    // Unmarshall my (user defined) ID and array ptr
    data_t* data_ptr = (data_t*) args;

    data_t mydata = *data_ptr;
    int myid = mydata.myid;
    int *arr_ptr = mydata.arr_ptr;
    
    cout << "\t\tHello World! I am thread "<< myid << endl;

    int chunk = -1, i_start = -1, i_end;
    
    // 1. I have more threads than elements
    if(SIZE < NUM_THREADS)
    {
        i_start = myid;
        i_end = myid + 1;
        chunk = 1;
        
        // Cutoff if i is out of bound due to high threadId
        if(myid > SIZE-1)
        {
            cout << "myid is " << myid << " - CUTOFF";
            return NULL;
        }
    }

    // 2. N is multiple of T
    else if(SIZE % NUM_THREADS == 0)
    {
        chunk = SIZE/NUM_THREADS;
        i_start = myid * chunk;
        i_end = i_start + chunk;
    }

    // 3. N is not multiple of T (yet, > T)
    else
    {
        chunk = SIZE/NUM_THREADS + 1;
        i_start = myid * chunk;

         // If I am last thread, adjust chunk
        if(myid == NUM_THREADS-1)
            chunk = SIZE/chunk;
        
        // Finally, I can adjust the i_end
        i_end = i_start + chunk;
    }

    cout << "\t\tI am thread " << myid
         << " chunk is " << chunk
         << " i_start is " << i_start
         << " i_end is " << i_end << endl;

    for(int i = i_start; i < i_end; i++)
        arr_ptr[i] = arr_ptr[i] * 2;

    return NULL;
}

int main()
{
    pthread_t mythread[NUM_THREADS];
    pthread_attr_t attr[NUM_THREADS];
    int res;

    int arr[SIZE];
    data_t data[NUM_THREADS];

    // Init my array
    for (unsigned int i = 0; i < SIZE; i++)
        arr[i] = i;

    cout << "SIZE is " << SIZE << " NUM_THREADS is " << NUM_THREADS << endl;
    // This is the work that I want to parallelize
    // You do data-paralelism when you want to accelerate loops
    //
    // for(unsigned int i=0; i<SIZE; i++)
    //     arr[i] = arr[i] * 2;

    cout << "Hello World! I am the MASTER thread, before creating slaves" << endl;
    for (unsigned int i = 1; i < NUM_THREADS; i++)      // ==> FORK
    {
        res = pthread_attr_init(&attr[i]);
        
        // Marshal data
        data[i].arr_ptr = &arr[0];
        data[i].myid = i;
                           
        // Define thread Id (user-defined), from 1 onwards,
        // and pass it as args (boxing & marshalling)                             
        res = pthread_create (&mythread[i],
                              &attr[i],
                              my_pthread_fn,
                              (void *) &data[i]
                             );
        
        if(res != 0)
        {
            cerr << "ERROR in pthread_create. OS returned " << res << endl;
            return -1;
        }
        res = pthread_attr_destroy(&attr[i]);
    }

    // I also take part into computation, by directly calling the BODY fn
    data[0].arr_ptr = &arr[0];
    data[0].myid = 0;
    my_pthread_fn(&data[0]); // I am thread #0

    void * returnvalue;
    cout << "Hello World! I am the MASTER thread, before joining slaves" << endl;
    
    for (unsigned int i = 1; i < NUM_THREADS; i++)      // <== JOIN
        res = pthread_join (mythread[i], &returnvalue);
    cout << "Hello World! I am the MASTER thread, after joining slaves" << endl;

    // Check results
    for (unsigned int i = 0; i < SIZE; i++)
        cout << "arr[" << i << "] is " << arr[i] << endl;
    return 0;
}