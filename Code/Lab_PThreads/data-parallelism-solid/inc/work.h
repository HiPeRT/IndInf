/*
 * Business API for the use cases
 */
#ifndef __WORK_H__
#define __WORK_H__

// This is the work that I want to parallelize
// You do data-paralelism when you want to accelerate loops
//
// for(unsigned int i=0; i<SIZE; i++)
//     arr[i] = arr[i] * 2;
void multiply_array(int *arr, int size);

#endif