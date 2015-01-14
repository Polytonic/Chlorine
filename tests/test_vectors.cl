// Fill Incrementing-Vector Array of Integers
__kernel void ifill(__global int4 * a)
{
    unsigned int i = get_global_id(0);
    a[i].x = 0;
    a[i].y = 1;
    a[i].z = 2;
    a[i].w = 3;
}

// Fill Incrementing-Vector Array of Floats
__kernel void ffill(__global float4 * a)
{
    unsigned int i = get_global_id(0);
    a[i].x = 0.0f;
    a[i].y = 1.0f;
    a[i].z = 2.0f;
    a[i].w = 3.0f;
}
