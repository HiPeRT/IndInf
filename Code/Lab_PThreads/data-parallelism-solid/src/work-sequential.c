/*
 * Sequential implementation
 */

void multiply_array(int *arr, int size)
{
    for(unsigned int i=0; i<size; i++)
        arr[i] = arr[i] * 2;
}