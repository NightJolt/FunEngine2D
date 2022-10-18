option(FE2D_LINUX "compile for linux" OFF)
option(FE2D_WINDOWS "compile for windows" ON)
option(FE2D_APPLE "compile for apple" OFF)

if (FE2D_LINUX)
	list(APPEND CPP_DEFINITIONS FE2D_LINUX)
elseif(FE2D_WINDOWS)
	list(APPEND CPP_DEFINITIONS FE2D_WINDOWS)
elseif(FE2D_APPLE)
	list(APPEND CPP_DEFINITIONS FE2D_APPLE)
endif()

option(FE2D_ENABLE_CUDA "enable cuda compilation" OFF)
option(FE2D_ENABLE_CUDA_SEPARABLE_COMPILATION "enable cuda separable compilation" OFF)

if (FE2D_ENABLE_CUDA)
	list(APPEND CPP_DEFINITIONS FE2D_CUDA)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(FE2D_DEBUG TRUE)
	list(APPEND CPP_DEFINITIONS FE2D_DEBUG)
else()
	set(FE2D_DEBUG FALSE)
	list(APPEND CPP_DEFINITIONS FE2D_RELEASE)
endif()


set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/libs/sfml")
set(CMAKE_MODULE_PATH "${SFML_ROOT}/lib/cmake")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
list(APPEND CPP_DEFINITIONS FE2D_SFML)

if (FE2D_DEBUG)
	set(ImGui-SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/imgui_sfml/debug/lib/cmake/ImGui-SFML")
else()
	set(ImGui-SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/imgui_sfml/release/lib/cmake/ImGui-SFML")
endif()
find_package(ImGui-SFML REQUIRED)
set(IMGUI_SFML_LIBS ImGui-SFML::ImGui-SFML)
list(APPEND CPP_DEFINITIONS FE2D_IMGUI)

set(box2d_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/box2d/lib/cmake/box2d")
find_package(box2d REQUIRED)
set(BOX2D_LIBS box2d::box2d)
list(APPEND CPP_DEFINITIONS FE2D_BOX2D)

add_subdirectory(core)

if (FE2D_ENABLE_CUDA)
	add_subdirectory(kernel)
endif()