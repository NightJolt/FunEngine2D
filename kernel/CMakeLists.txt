set(CMAKE_CUDA_STANDARD 20)

include_directories(header_files)
include_directories(source_files)

file (
        GLOB_RECURSE KERNEL_FILES

        header_files/*.cuh
        source_files/*.cu
)

add_library(kernel_lib ${KERNEL_FILES})

set_target_properties(kernel_lib PROPERTIES CUDA_SEPARABLE_COMPILARION ON)
target_link_libraries(kernel_lib)