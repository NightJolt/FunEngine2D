#include "globals.h"

sf::RenderWindow* glob_window;

void fun::glob_init() {
#if defined(ENABLE_DEBUGGING)
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
#endif

// #if defined(USES_IMGUI)
//     ImGui::GetIO().IniFilename = nullptr;
// #endif
}

fun::UniqueKey::UniqueKey(void* p, const char* k) : ptr(p), key(strdup(k)) {}

fun::UniqueKey::~UniqueKey() { free(key); }

bool fun::UniqueKey::operator <(const UniqueKey& other) const {
    return strcmp(key, other.key) < 0;
}

fun::UniqueKey::UniqueKey(const UniqueKey& other) {
    ptr = other.ptr;
    key = strdup(other.key);
}

fun::UniqueKey& fun::UniqueKey::operator =(const UniqueKey& other) {
    if (&other == this) return *this;

    ptr = other.ptr;
    key = strdup(other.key);

    return *this;
}

fun::UniqueKey::UniqueKey(UniqueKey&& other) noexcept {
    ptr = other.ptr;
    key = other.key;

    other.ptr = nullptr;
    other.key = nullptr;
}