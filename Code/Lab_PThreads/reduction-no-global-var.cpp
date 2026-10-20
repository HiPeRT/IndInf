/*
 Here we compute the average value of an array, in parallel.
 We use the REDUCTION paralel pattern.
*/

#include <iostream>
using namespace std;

#include <pthread.h>

// Thiese are global, because we want it to be visible both to main() and pthread_fn()
// NOTE as a genral rule, we should NEVER work on global objects, as they represent an uncontrolled dependency
#define N_ELEM 16

typedef struct data_s
{
    int *arr_ptr;
    int myid;
    int *local_sum;
} data_t;

#define NUM_THREADS 4


void * pthreads_fn(void * args)
{
    // Unmarshall my (user defined) ID
    data_t* data_ptr = (data_t*) args;

    data_t mydata = *data_ptr;
    int myid = mydata.myid;
    int *arr_ptr = mydata.arr_ptr;
    int *local_sum = mydata.local_sum;

    // Init my local sum
    *local_sum = 0;
    
    // NOTE We assume N_ELEM is a multiple of NUM_THREADS!
    // See deck 07 of slides for treating other cases.
    int chunk = N_ELEM / NUM_THREADS;
    int istart = chunk * myid;
    int iend = istart + chunk;

    for(int i = istart; i<iend; i++ )
        *local_sum = *local_sum + arr_ptr[i];

    return NULL;
}

int main()
{
    pthread_t mythreads[NUM_THREADS];
    pthread_attr_t myattr;
    
    int arr[N_ELEM];
    data_t data[NUM_THREADS];
    // Local sums (for Reduction pattern)
    int sum_local[NUM_THREADS];

    // To store pthreads' return val (not used here, else we'd need an array of these,
    // one for each thread)
    void *returnvalue;

    float avg_expected = 0.0;
    // Init arr (randomly) and compute expected result
    for(int i=0; i<N_ELEM; i++)
    {
        arr[i]= i;
        avg_expected += arr[i];
    }
    avg_expected /= N_ELEM;
    
    for(int i=1; i<NUM_THREADS; i++)                        // ==> FORK
    {
        pthread_attr_init(&myattr);

        // Marshal data
        data[i].arr_ptr = &arr[0];
        data[i].myid = i;
        data[i].local_sum = &sum_local[i];
        // Pass 'i' as the progressive identifier for thread (last argument of pthread_create)
        int err = pthread_create (&mythreads[i], &myattr, pthreads_fn, (void *) &data[i]);
        
        pthread_attr_destroy(&myattr);
    }

    // We want the master thread to do the very same work of other threads
    // Master thread has ID '0'
    data[0].arr_ptr = &arr[0];
    data[0].myid = 0;
    data[0].local_sum = &sum_local[0];
    pthreads_fn((void *) &data[0]);
    
    for(int i=1; i<NUM_THREADS; i++)                        // <== JOIN
        pthread_join(mythreads[i], &returnvalue);

    int sum = 0;
    for(int i=0; i<NUM_THREADS; i++)
        sum += sum_local[i];
    float avg = ((float) sum) / N_ELEM;

    // Check (after join!!)
    cout << "[CHECK] average value is " << avg << " (expected " << avg_expected << ")" << endl;

    return 0;
}