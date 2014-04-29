// OpenCL Extensions
#pragma OPENCL EXTENSION cl_khr_fp16 : enable
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__kernel void add(__global int * a, __global float * b, float c, __global int * d)
{
    unsigned int i = get_global_id(0);
    a[i] += d[i];
    b[i] += c;
}
