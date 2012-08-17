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
