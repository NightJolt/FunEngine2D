cmake_minimum_required(VERSION 3.19.2)
project(FunEngine2D LANGUAGES CXX CUDA)

#find_package(Lua REQUIRED)
#find_package(ImGui-SFML REQUIRED)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES "/opt/cuda/bin/nvcc")
set(GCC_COVERAGE_COMPILE_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network ")
# -Ofast -pthread -lm -lGL -L/usr/X11R6/lib -lGLU -lGLEW -lXi -lXmu
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(source)

file (
        GLOB_RECURSE SOURCE_FILES

        source/*.cpp
)

add_executable(FunEngine2D ${SOURCE_FILES})

add_subdirectory(fun_engine_2d)

target_link_libraries(FunEngine2D fe2d_source)
target_link_libraries(FunEngine2D fe2d_kernel)
#target_link_libraries(FunEngine2D ${LUA_LIBRARIES})
#target_link_libraries(FunEngine2D PRIVATE ImGui-SFML::ImGui-SFML)