set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD 20)

include_directories(include)
include_directories(source)

file (
        GLOB_RECURSE FE2D_SOURCE

        include/*.h
        source/*.cpp
)

file (
        GLOB_RECURSE FE2D_KERNEL

        include/experimental/kernel/*.cuh
        source/experimental/kernel/*.cu
)

add_library(fe2d_source ${FE2D_SOURCE})
add_library(fe2d_kernel ${FE2D_KERNEL})

set_target_properties(fe2d_kernel PROPERTIES CUDA_SEPARABLE_COMPILARION ON)