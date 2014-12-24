// Adds Two Integers
__kernel void add(__global int * a, __global int * b, __global int * c)
{
    unsigned int i = get_global_id(0);
    c[i] = a[i] + b[i];
}

/*

    test<int, float>()
        array<int>, array<float>
        array<int>, valarray<float>
        valarray<int>, valarray<float>


    test<valarray>

        valarray<int>, <int>
        valarray<int>, <float>

*/
