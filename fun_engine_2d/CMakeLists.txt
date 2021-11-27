add_subdirectory(core)
add_subdirectory(experimental)

if (UNIX)
	add_subdirectory(kernel)
endif()

target_link_libraries(${PROJECT_NAME} fe2d_core)
target_link_libraries(${PROJECT_NAME} fe2d_experimental)

if (UNIX)
	target_link_libraries(${PROJECT_NAME} fe2d_kernel)
endif()