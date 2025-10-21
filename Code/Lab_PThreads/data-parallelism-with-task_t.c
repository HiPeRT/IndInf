#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 16
#define SIZE 16

typedef struct data_s
{
    int *arr_ptr;
    int myid;
} data_t;

typedef struct task_s
{
    // As per POSIX standard, this is a function pointer
    // that accepts a void pointer
    // and returns a void pointer
    void *(*body)(void *);
    void * arg; // Data payload
} task_t;

/*
 * This function is the code of PThread
 */
void * my_pthread_fn(void* args)
{
    // Unmarshall my (user defined) ID
    data_t* data_ptr = (data_t*) args;

    data_t mydata = *data_ptr;
    int my_id = mydata.myid;
    int *arr_ptr = mydata.arr_ptr;
    
    printf("\t\t\t\t\tHello World! I am a thread %d, and the OS assigned me the ID %lu\n", my_id, pthread_self());

    // Do my work. I use my ID as array index. So,
    //  Thread 0 -> arr[0]
    //  Thread 1 -> arr[1]
    //  Thread 2 -> arr[2]
    //  ...and so on...
    //
    // This means, that the amount of work (my CHUNK) is 1
    arr_ptr[my_id] = arr_ptr[my_id] * 2;

    return NULL;
}

int main()
{
    pthread_t mythread[NUM_THREADS];
    pthread_attr_t attr[NUM_THREADS];
    int res;

    int arr[SIZE];
    data_t data[NUM_THREADS];
    task_t tasks[NUM_THREADS];

    // Init my array
    for (unsigned int i = 0; i < SIZE; i++)
        arr[i] = i;

    // This is the work that I want to parallelize
    // You do data-paralelism when you want to accelerate loops
    //
    // for(unsigned int i=0; i<SIZE; i++)
    //     arr[i] = arr[i] * 2;

    printf("Hello World! I am the MASTER thread, before creating slaves\n");
    for (unsigned int i = 1; i < NUM_THREADS; i++)      // ==> FORK
    {
        res = pthread_attr_init(&attr[i]);
        
        // Marshal data
        data[i].arr_ptr = &arr[0];
        data[i].myid = i;

        // Marshal task
        tasks[i].body = my_pthread_fn;
        tasks[i].arg = &data[i];
                           
        // Define thread Id (user-defined), from 1 onwards,
        // and pass it as args (boxing/marshalling)                             
        res = pthread_create (&mythread[i],
                              &attr[i],
                              tasks[i].body,
                              (void *) tasks[i].data
                             );
        
        if(res != 0)
        {
            printf("ERROR in pthread_create. OS returned %d\n", res);
            return -1;
        }
        res = pthread_attr_destroy(&attr[i]);
    }

    // I also take part into computation, by directly calling the BODY fn
    data[0].arr_ptr = &arr[0];
    data[0].myid = 0;
    my_pthread_fn(&data[0]); // I am thread #0

    void * returnvalue;
    printf("Hello World! I am the MASTER thread, before joining slaves\n");
    
    for (unsigned int i = 1; i < NUM_THREADS; i++)      // <== JOIN
        res = pthread_join (mythread[i], &returnvalue);

    printf("Hello World! I am the MASTER thread, after joining slaves\n");

    // Check results
    for (unsigned int i = 0; i < SIZE; i++)
        printf("arr[%u] is %d\n", i, arr[i]);

    // Additional note. Checking the correctness of results by printing them on screen
    // is not efficient, because you cannot automate this test. For this reason,
    // most of engineers prefer to create a checksum and assess against it.

    /*
    int expected_checksum = 0, checksum = 0;
    for (int i=0; i<SIZE; i++)
        expected_checksum += (i*2);

    for (int i=0; i<SIZE; i++)
        checksum += arr[i];

    if(checksum == expected_checksum)
        printf("--- Checksum correct! Good job!\n");
    else
        printf("--- Checksum FAIL! Your program has something wrong.\n");

    // ..or..
    // assert(expected_checksum, checksum);
    */
    return 0;
}