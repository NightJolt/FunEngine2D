set(LIB_NAME "fe2d_core")

include_directories(include)
include_directories(source)

file (
    GLOB_RECURSE FE2D_CORE

    include/*.h
    source/*.cpp
)

add_library(${LIB_NAME} ${FE2D_CORE})

target_include_directories(${LIB_NAME} PUBLIC include})
target_include_directories(${LIB_NAME} PUBLIC source})

target_link_libraries(${LIB_NAME} ${SFML_LIBS})
target_link_libraries(${LIB_NAME} ${IMGUI_SFML_LIBS})
target_link_libraries(${LIB_NAME} ${BOX2D_LIBS})

target_compile_definitions(${LIB_NAME} PUBLIC ${CPP_DEFINITIONS})