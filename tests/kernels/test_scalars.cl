// Uniformly Fill Scalar Array of Integers
__kernel void ifill(__global int * a, int b)
{
    unsigned int i = get_global_id(0);
    a[i] = b;
}

// Uniformly Fill Scalar Array of Floats
__kernel void ffill(__global float * a, float b)
{
    unsigned int i = get_global_id(0);
    a[i] = b;
}
