#include "object_system/Level.h"

fun::Level::Level() : static_objects(std::vector <StaticObject*> ()), live_objects(std::vector <LiveObject*> ())  {}

void fun::Level::Init() {
    for (auto obj : static_objects) {
        obj->Init();
    }

    for (auto obj : live_objects) {
        obj->Init();
    }
}

void fun::Level::Update() {
    for (auto obj : live_objects) {
        obj->Update();
    }
}

void fun::Level::Dispose() {
    for (auto obj : static_objects) {
        obj->Dispose();
    }

    for (auto obj : live_objects) {
        obj->Dispose();
    }
}
