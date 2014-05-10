// Swap the Contents of Two Arrays
__kernel void swap(__global float * a, __global float *b)
{
    unsigned int i = get_global_id(0);
    float swap = a[i];
    a[i] = b[i];
    b[i] = swap;
}

// Add Primitive to Each Element in Given Array
__kernel void add(__global float * a, float b)
{
    unsigned int i = get_global_id(0);
    a[i] += b;
}
