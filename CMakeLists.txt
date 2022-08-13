option(FE2D_LINUX "compile for linux" OFF)
option(FE2D_WINDOWS "compile for windows" ON)
option(FE2D_APPLE "compile for apple" OFF)

option(FE2D_ENABLE_CUDA "enable cuda compilation" OFF)
option(FE2D_ENABLE_CUDA_SEPARABLE_COMPILATION "enable cuda separable compilation" OFF)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(FE2D_DEBUG TRUE)
else()
	set(FE2D_DEBUG FALSE)
endif()


set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/libs/sfml")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/lib/cmake")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

if (FE2D_DEBUG)
	set(ImGui-SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/imgui_sfml/debug/lib/cmake/ImGui-SFML")
else()
	set(ImGui-SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/imgui_sfml/release/lib/cmake/ImGui-SFML")
endif()
find_package(ImGui-SFML REQUIRED)
set(IMGUI_SFML_LIBS ImGui-SFML::ImGui-SFML)

set(box2d_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/box2d/lib/cmake/box2d")
find_package(box2d REQUIRED)
set(BOX2D_LIBS box2d::box2d)

add_subdirectory(core)

if (FE2D_ENABLE_CUDA)
	add_subdirectory(kernel)
endif()