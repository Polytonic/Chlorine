__kernel void swap(__global float * spam, __global float * eggs)
{
    unsigned int i = get_global_id(0);
    float swap = spam[i];
    spam[i] = eggs[i];
    eggs[i] = swap;
}
