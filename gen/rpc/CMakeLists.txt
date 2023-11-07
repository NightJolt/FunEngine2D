project(fe2d_rpc_gen)

include_directories(include)
include_directories(source)

file (
    GLOB_RECURSE SOURCE_FILES

    main.cpp

    include/*.h
    source/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} fe2d_core)

target_compile_definitions(${PROJECT_NAME} PUBLIC ${CPP_DEFINITIONS})