#include "globals.h"

void fun::glob_init() {
    DEBUG_CODE(std::ios::sync_with_stdio(false));
    DEBUG_CODE(std::cin.tie(nullptr); std::cout.tie(nullptr));

// #if defined(FE2D_IMGUI)
//     ImGui::GetIO().IniFilename = nullptr;
// #endif
}