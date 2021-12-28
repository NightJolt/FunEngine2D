#include "ecs/Entity.h"

fun::Entity::~Entity() noexcept = default;

void fun::Entity::Init() {}

void fun::Entity::Dispose() {
    should_be_disposed = true;
}