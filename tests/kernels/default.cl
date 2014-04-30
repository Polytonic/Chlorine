
__kernel void add(__global int * a, __global int * b, int c,
  __global float * d, __global float * e, float f,
  __global int * g, __global int * h)

{
    unsigned int i = get_global_id(0);
    a[i] += b[i] + c;
    d[i] += e[i] + f;
    g[i] += h[i] + c;
}
