cmake_minimum_required(VERSION 3.17)
project(FunEngine2D)

#find_package(Lua REQUIRED)
#find_package(ImGui-SFML REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(GCC_COVERAGE_COMPILE_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network")
# -Ofast -pthread -lm -lGL -L/usr/X11R6/lib -lGLU -lGLEW -lXi -lXmu
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(header-files)
include_directories(source-files)
include_directories(core-header-files)
include_directories(core-source-files)

file (GLOB_RECURSE SOURCE_FILES
        header-files/*.h
        source-files/*.cpp
        core-header-files/*.h
        core-source-files/*.cpp
)

add_executable(FunEngine2D ${SOURCE_FILES})

#target_link_libraries(FunEngine2D ${LUA_LIBRARIES})
#target_link_libraries(ImageFilter PRIVATE ImGui-SFML::ImGui-SFML)