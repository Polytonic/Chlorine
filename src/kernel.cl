// OpenCL Extensions
#pragma OPENCL EXTENSION cl_khr_fp16 : enable
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

// Precision Declaration
typedef float  Scalar;
typedef float4 Float;

// Pre-Processor Directives
#define Pi 3.1415f

// Example Kernel Utilizing Vector Operations
__kernel void Chlorine_Demo(__global Float * a, __global Float * b)
{
    unsigned int i = get_global_id(0);
    b[i].w = cos(a[i].x);
    a[i] += Pi;
    b[i] -= a[i];
    a[i].x = 2.71828f;
    b[i] *= (Float) ( 0.1f, 2.3f, 5.7f, 11.13f );
}