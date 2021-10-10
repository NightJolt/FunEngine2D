set(CMAKE_CXX_STANDARD 20)

include_directories(include)
include_directories(source)

file (
        GLOB_RECURSE FE2D_EXPERIMENTAL

        include/*.h
        source/*.cpp
)

add_library(fe2d_experimental ${FE2D_EXPERIMENTAL})