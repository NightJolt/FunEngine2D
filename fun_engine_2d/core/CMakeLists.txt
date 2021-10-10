set(CMAKE_CXX_STANDARD 20)

include_directories(include)
include_directories(source)

file (
        GLOB_RECURSE FE2D_CORE

        include/*.h
        source/*.cpp
)

add_library(fe2d_core ${FE2D_CORE})