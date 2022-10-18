#include "globals.h"

void fun::glob_init() {
#if defined(FE2D_DEBUG)
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
#endif

// #if defined(FE2D_IMGUI)
//     ImGui::GetIO().IniFilename = nullptr;
// #endif
}