// Adds Two Floats
__kernel void add(__global float * a, __global float * b, __global float * c)
{
    unsigned int i = get_global_id(0);
    c[i] = a[i] + b[i];
}

// Subtracts Two Floats
__kernel void sub(__global float * a, __global float * b, __global float * c)
{
    unsigned int i = get_global_id(0);
    c[i] = a[i] - b[i];
}

// Multiplies Two Floats
__kernel void mul(__global float * a, __global float * b, __global float * c)
{
    unsigned int i = get_global_id(0);
    c[i] = a[i] * b[i];
}
