
__kernel void add(__global int * a, __global float * b, float c, __global int * d)
{
    unsigned int i = get_global_id(0);
    a[i] += d[i];
    b[i] += c;
}
