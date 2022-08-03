#include "cudatest.cuh"

// #include <curand.h>
// #include <curand_kernel.h>

// #include <cuda_runtime.h>
// #include <device_launch_parameters.h>
#include <windows.h>
// #include <WinGDI.h>
#include <cuda_gl_interop.h>

__global__ void cadd(int32_t* a, int32_t* b, int32_t* c) {
    *c = *a + *b;
}

int fun::cudatest::add_two_numbers(int32_t host_a, int32_t host_b) {
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

    cudaFree(device_a);
    cudaFree(device_b);
    cudaFree(device_c);

    return host_c;
}