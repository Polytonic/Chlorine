// Test the Chlorine Stream Operators
__kernel void read(__global int * a)
{
    unsigned int i = get_global_id(0);
    a[i] = 0
}
