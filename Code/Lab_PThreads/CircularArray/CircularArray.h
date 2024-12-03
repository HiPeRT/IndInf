#ifndef __CIRCULAR_ARRAY_H__
#define __CIRCULAR_ARRAY_H__

#include <semaphore.h>

#define SIZE_CA 10

struct CircularArray_t {
  int array[SIZE_CA];
  int head, tail;
  sem_t empty, full;
};

/*
 * Initialze the CA
 * Returns 0 on success; <0 on failure
 */
int init_CA (struct CircularArray_t *c);

/*
 * Thread-safe insertion of elements. Blocking if the queue is full.
 */
void insert_CA (struct CircularArray_t *c, int elem);

/*
 * Thread-safe extraction of elements. Blocking if the queue is empty.
 */
void extract_CA (struct CircularArray_t *c, int *elem);

#endif