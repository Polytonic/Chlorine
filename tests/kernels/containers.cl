// Swap the Contents of Two Arrays
__kernel void swap(__global int * a, __global int *b)
{
    unsigned int i = get_global_id(0);
    int swap = a[i];
    a[i] = b[i];
    b[i] = swap;
}
