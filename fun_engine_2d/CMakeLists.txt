set(CMAKE_CXX_STANDARD 20)

add_subdirectory(core)
add_subdirectory(experimental)
add_subdirectory(kernel)

target_link_libraries(${PROJECT_NAME} fe2d_core)
target_link_libraries(${PROJECT_NAME} fe2d_experimental)
target_link_libraries(${PROJECT_NAME} fe2d_kernel)