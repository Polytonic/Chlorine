// OpenCL Extensions
#pragma OPENCL EXTENSION cl_khr_fp16 : enable
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__kernel void add(__global int * a, __global float * b, int c)
{
    unsigned int i = get_global_id(0);
    a[i] += c;
    b[i] += 3.0f;

}
