/*
 * PThreads-based implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "debug.h"

/*
 * This is the task data structure *used for marshalling and unmarshalling)
 */
typedef struct data_s
{
    int *arr_ptr;
    int myid;
    int size;
    int nthreads;
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
    int size = mydata.size;
    int nthreads = mydata.nthreads;
    
    //debug("\t\tHello World! I am thread %d\n", myid);

    int chunk = -1, i_start = -1, i_end;
    
    // 1. I have more threads than elements
    if(size < nthreads)
    {
        i_start = myid;
        i_end = myid + 1;
        chunk = 1;
        
        // Cutoff if i is out of bound due to high threadId
        if(myid > size-1)
        {
            debug("\t\tI am thread %d - CUTOFF\n", myid);
            return NULL;
        }
    }

    // 2. N is multiple of T
    else if(size % nthreads == 0)
    {
        chunk = size/nthreads;
        i_start = myid * chunk;
        i_end = i_start + chunk;
    }

    // 3. N is not multiple of T (yet, > T)
    else
    {
        chunk = size/nthreads + 1;
        i_start = myid * chunk;

         // If I am last thread, adjust chunk
        if(myid == nthreads-1)
            chunk = size/chunk;
        
        // Finally, I can adjust the i_end
        i_end = i_start + chunk;
    }

    debug("\t\tI am thread %d chunk is %d i_start is %d i_end is %d\n",
            myid, chunk, i_start, i_end);

    for(int i = i_start; i < i_end; i++)
        arr_ptr[i] = arr_ptr[i] * 2;

    return NULL;
}

/*
 * This function returns the number of threads that we shall actually use
 */
int get_threads_nr(int size)
{
    // We can implement more complex policies here
    return 16;
}

void multiply_array(int *arr, int size)
{
    int nthreads = get_threads_nr(size);
    pthread_t mythread[nthreads];
    pthread_attr_t attr[nthreads];
    data_t data[nthreads];
    int res;

    debug("nthreads is %d\n", nthreads);

    for (unsigned int i = 1; i < nthreads; i++)      // ==> FORK
    {
        res = pthread_attr_init(&attr[i]);
        
        // Marshal data
        data[i].arr_ptr = &arr[0];
        data[i].myid = i;
        data[i].size = size;
        data[i].nthreads = nthreads;
                           
        // Define thread Id (user-defined), from 1 onwards,
        // and pass it as args (boxing & marshalling)                             
        res = pthread_create (&mythread[i],
                              &attr[i],
                              my_pthread_fn,
                              (void *) &data[i]
                             );
        
        if(res != 0)
        {
            error("ERROR in pthread_create. OS returned %d\n", res);
            exit(-1);
        }
        res = pthread_attr_destroy(&attr[i]);
    }

    // I also take part into computation, by directly calling the BODY fn
    data[0].arr_ptr = &arr[0];
    data[0].myid = 0;
    data[0].size = size;
    data[0].nthreads= nthreads;
    my_pthread_fn(&data[0]); // I am thread #0

    void * returnvalue;
    debug("I am the MASTER thread, before joining slaves\n");
    
    for (unsigned int i = 1; i < nthreads; i++)      // <== JOIN
        res = pthread_join (mythread[i], &returnvalue);
    debug("I am the MASTER thread, after joining slaves\n");
}