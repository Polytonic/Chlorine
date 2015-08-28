// Adds Two Integers
__kernel void add(__global int * a, __global int * b, __global int * c)
{
    unsigned int i = get_global_id(0);
    c[i] = a[i] + b[i];
}

// Subtracts Two Integers
__kernel void sub(__global int * a, __global int * b, __global int * c)
{
    unsigned int i = get_global_id(0);
    c[i] = a[i] - b[i];
}

// Multiplies Two Integers
__kernel void mul(__global int * a, __global int * b, __global int * c)
{
    unsigned int i = get_global_id(0);
    c[i] = a[i] * b[i];
}
