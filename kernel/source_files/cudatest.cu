#include "cudatest.cuh"

__global__ void cadd(int* a, int* b, int* c) {
    *c = *a + *b;
}

int fun::CudaTesting::AddTwoNumbers(int host_a, int host_b) {
    int host_c;

    int* device_a;
    int* device_b;
    int* device_c;

    cudaMalloc(&device_a, sizeof(int));
    cudaMalloc(&device_b, sizeof(int));
    cudaMalloc(&device_c, sizeof(int));

    cudaMemcpy(device_a, &host_a, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(device_b, &host_b, sizeof(int), cudaMemcpyHostToDevice);

    cadd <<<1, 1>>> (device_a, device_b, device_c);

    cudaMemcpy(&host_c, device_c, sizeof(int), cudaMemcpyDeviceToHost);

    return host_c;
}