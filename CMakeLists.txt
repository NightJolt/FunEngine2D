if (UNIX AND NOT APPLE)
	list(APPEND CPP_DEFINITIONS FE2D_LINUX)
elseif(WIN32)
	list(APPEND CPP_DEFINITIONS FE2D_WINDOWS)
elseif(APPLE)
	list(APPEND CPP_DEFINITIONS FE2D_APPLE)
endif()


option(FE2D_ENABLE_MOUSE "enable mouse input" ON)
option(FE2D_ENABLE_KEYBOARD "enable keyboard input" ON)
option(FE2D_ENABLE_GAMEPAD "enable gamepad input" OFF)

if (FE2D_ENABLE_MOUSE)
	list(APPEND CPP_DEFINITIONS FE2D_MOUSE)
endif()
if(FE2D_ENABLE_KEYBOARD)
	list(APPEND CPP_DEFINITIONS FE2D_KEYBOARD)
endif()
if(FE2D_ENABLE_GAMEPAD)
	list(APPEND CPP_DEFINITIONS FE2D_GAMEPAD)
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


option(FE2D_ENABLE_SFML "enable sfml" ON)

if (FE2D_ENABLE_SFML)
	set(SFML_ROOT "${CMAKE_CURRENT_LIST_DIR}/libs/sfml")
	set(CMAKE_MODULE_PATH "${SFML_ROOT}/lib/cmake")
	set(SFML_STATIC_LIBRARIES TRUE)
	find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
	set(SFML_LIBS sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
	list(APPEND CPP_DEFINITIONS FE2D_SFML)
endif()


option(FE2D_ENABLE_IMGUI "enable imgui" ON)

if (FE2D_ENABLE_IMGUI)
	if (FE2D_DEBUG)
		set(ImGui-SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/imgui_sfml/debug/lib/cmake/ImGui-SFML")
	else()
		set(ImGui-SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/imgui_sfml/release/lib/cmake/ImGui-SFML")
	endif()
	find_package(ImGui-SFML REQUIRED)
	set(IMGUI_SFML_LIBS ImGui-SFML::ImGui-SFML)
	list(APPEND CPP_DEFINITIONS FE2D_IMGUI)
endif()


option(FE2D_ENABLE_BOX2D "enable box2d" ON)

if (FE2D_ENABLE_BOX2D)
	set(box2d_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/box2d/lib/cmake/box2d")
	find_package(box2d REQUIRED)
	set(BOX2D_LIBS box2d::box2d)
	list(APPEND CPP_DEFINITIONS FE2D_BOX2D)
endif()

list(APPEND CPP_DEFINITIONS ROOT_DIRECTORY="${CMAKE_SOURCE_DIR}")

add_subdirectory(core)

add_subdirectory(gen)

if (FE2D_ENABLE_CUDA)
	add_subdirectory(kernel)
endif()