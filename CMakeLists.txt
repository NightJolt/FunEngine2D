set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/libs/sfml")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/lib/cmake")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

set (ImGui-SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/imgui_sfml/lib/cmake/ImGui-SFML")
set(IMGUI_SFML_LIBS ImGui-SFML::ImGui-SFML)
find_package(ImGui-SFML REQUIRED)

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