#include "../../include/core/globals.h"

sf::RenderWindow* glob_window;

void glob_init() {
#if defined(ENABLE_DEBUGGING)
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
#endif
}