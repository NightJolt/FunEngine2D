#include "Globals.h"

void fun::glob_init() {
#if defined(DEBUG_BUILD)
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
#endif

// #if defined(USES_IMGUI)
//     ImGui::GetIO().IniFilename = nullptr;
// #endif
}