set(CMAKE_CUDA_STANDARD 20)
set(LIB_NAME "fe2d_kernel")

project(LIB_NAME CUDA CXX)

find_package(CUDA 11.6 REQUIRED)

include_directories(include)
include_directories(source)

file (
	GLOB_RECURSE FE2D_KERNEL

	include/*.cuh
	source/*.cu
)

add_library(${LIB_NAME} ${FE2D_KERNEL})

if (FE2D_ENABLE_CUDA_SEPARABLE_COMPILATION)
	set_target_properties(${LIB_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
endif()

target_link_libraries(${LIB_NAME} ${CUDA_LIBRARIES})