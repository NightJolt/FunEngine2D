set(LIB_NAME "fe2d_experimental")

include_directories(include)
include_directories(source)

file (
        GLOB_RECURSE FE2D_EXPERIMENTAL
        
        source/*.cpp
)

add_library(${LIB_NAME} ${FE2D_EXPERIMENTAL})

target_link_libraries(${LIB_NAME} ${SFML_LIBS})
target_link_libraries(${LIB_NAME} ${IMGUI_SFML_LIBS})
target_link_libraries(${LIB_NAME} ${BOX2D_LIBS})