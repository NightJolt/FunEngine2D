#include "uuid.h"

// ? use math::random_64
static std::random_device _random_device_;
static std::mt19937_64 _engine_(_random_device_());
static std::uniform_int_distribution _uniform_distribution_;

uint64_t fun::uuid::generate() {
    return _uniform_distribution_(_engine_);
}