#include "Globals.h"

void fun::glob_init() {
#if defined(ENABLE_DEBUGGING)
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
#endif

// #if defined(USES_IMGUI)
//     ImGui::GetIO().IniFilename = nullptr;
// #endif
}

fun::UniqueKey::UniqueKey() : uuid(0), key("") {}

fun::UniqueKey::UniqueKey(uuid_t uuid, const char* _key) : uuid(uuid) {
    assert(sizeof _key <= sizeof key);

    strncat(key, _key, sizeof key);
}

// fun::UniqueKey::~UniqueKey() { free(key); }

fun::UniqueKey::UniqueKey(const UniqueKey& other) {
    uuid = other.uuid;
    strncat(key, other.key, sizeof key);
}

fun::UniqueKey& fun::UniqueKey::operator =(const UniqueKey& other) {
    if (&other == this) return *this;

    uuid = other.uuid;
    strncat(key, other.key, sizeof key);

    return *this;
}

fun::UniqueKey::UniqueKey(UniqueKey&& other) noexcept {
    uuid = other.uuid;
    strncat(key, other.key, sizeof key);

    other.uuid = 0;
}

fun::UniqueKey::operator uint64_t() const {
    return uuid;
}

static std::random_device _random_device_;
static std::mt19937_64 _engine_(_random_device_());
static std::uniform_int_distribution _uniform_distribution_;

uint64_t fun::uuid::generate() {
    return _uniform_distribution_(_engine_);
}