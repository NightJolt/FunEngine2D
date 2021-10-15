#include "object_system/Object.h"

fun::Object::~Object() noexcept = default;

void fun::Object::Init() {}

void fun::Object::Dispose() {
    should_be_disposed = true;
}