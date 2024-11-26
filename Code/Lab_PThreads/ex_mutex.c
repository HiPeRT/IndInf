/*
 * Semaphore demo 
 *
 * Copyright (C) 2002 by Paolo Gai
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mymutex;

void *body(void *arg)
{
    char *mychar = (char *) arg; // Unboxing of function params

    /*
     * int pthread_mutex_lock(pthread_mutex_t*m);
     * int pthread_mutex_unlock(pthread_mutex_t*m);
     */

    //pthread_mutex_lock(&mymutex);
    for(int i=0; i<40; i++)
    {
        pthread_mutex_lock(&mymutex);
        for(int j=0; j<20; j++)
        {
            printf("%c", *mychar);
        }
        //printf("\n");
        pthread_mutex_unlock(&mymutex);
    }
    //pthread_mutex_unlock(&mymutex);
}

int main()
{
    pthread_t t1,t2,t3;
    pthread_attr_t myattr;
    int err;
    pthread_mutexattr_t mymutexattr;

    /*
     * int pthread_mutex_init(pthread_mutex_t*mutex,
     *                        const pthread_mutexattr_t*attr);
     */
    pthread_mutexattr_init(&mymutexattr);
    pthread_mutex_init(&mymutex, &mymutexattr);
    pthread_mutexattr_destroy(&mymutexattr);

    pthread_attr_init(&myattr);
    err = pthread_create(&t1, &myattr, body, (void *)"."); // Boxing of parameters
    err = pthread_create(&t2, &myattr, body, (void *)"#");
    err = pthread_create(&t3, &myattr, body, (void *)"o");
    pthread_attr_destroy(&myattr);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);    

    /* int pthread_mutex_destroy(pthread_mutex_t*mutex); */
    err = pthread_mutex_destroy(&mymutex);

    return 0;
}