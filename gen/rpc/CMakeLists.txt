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

function(fe2d_rpc_gen namespace rpc_file_name rpc_file_path)
    if (FE2D_WINDOWS)
        set(RPC_BIN "${CMAKE_BINARY_DIR}/FunEngine2D/gen/rpc/fe2d_rpc_gen.exe")
    else()
        set(RPC_BIN "${CMAKE_BINARY_DIR}/FunEngine2D/gen/rpc/fe2d_rpc_gen")
    endif()

    message("generating rpc files")
    execute_process(COMMAND "${RPC_BIN}" "${CMAKE_CURRENT_SOURCE_DIR}/${rpc_file_path}/${rpc_file_name}.rpc" "${CMAKE_BINARY_DIR}/rpc/${namespace}/${rpc_file_name}.h")
endfunction()