set(CMAKE_CUDA_STANDARD 20)
set(LIB_NAME "fe2d_kernel")

include_directories(include)
include_directories(source)

file (
        GLOB_RECURSE FE2D_KERNEL

        include/*.cuh
        source/*.cu
)

add_library(${LIB_NAME} ${FE2D_KERNEL})

set_target_properties(${LIB_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)