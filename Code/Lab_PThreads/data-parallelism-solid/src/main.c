#include <stdio.h>
#include "work.h"
#include "debug.h"

int main()
{
    const int size = 8;
    int arr[size];
    debug("size is %d\n", size);

    // Init my array
    for (unsigned int i = 0; i < size; i++)
        arr[i] = i;

    // Do your work
    multiply_array(&arr[0], size);    

    // Check results
    for (unsigned int i = 0; i < size; i++)
        debug("arr[%d] is %d\n", i, arr[i]);
    return 0;
}