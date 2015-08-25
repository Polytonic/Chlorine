// Test the Kernel Read Function
__kernel void fill(__global int * a)
{
    unsigned int i = get_global_id(0);
    a[i] = 1;
}
