__kernel void assignLocal(__global int* A, __global int* B, __global int* C)
{
    int tid = get_global_id(0);
    C[tid] = 1;
}
__kernel void assignGlobal(__global int* A, __global int* B, __global int* C)
{
    int tid = get_global_id(0);
    C[tid] = A[tid];
}
__kernel void vecAdd(__global int* A, __global int* B, __global int* C)
{
    int tid = get_global_id(0);
    C[tid] = A[tid] + B[tid];
}

__kernel void assignLocalMany(__global int* A, __global int* B, __global int* C)
{
    int tid = get_global_id(0);
    int total = 0;
    for (int i = 0; i < 1024; i++)
        total += i;
    C[tid] = total;
}
__kernel void assignGlobalMany(__global int* A, __global int* B, __global int* C)
{
    int tid = get_global_id(0);
    for (int i = 0; i < 1024; i++)
        C[tid] += A[tid];
}
__kernel void vecAddMany(__global int* A, __global int* B, __global int* C)
{
    int tid = get_global_id(0);
    for (int i = 0; i < 1024; i++)
        C[tid] += A[tid] + B[tid];
}
