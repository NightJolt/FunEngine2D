#include "object_system/Level.h"

fun::Level::Level(const std::string& name) : name(name), static_objects(std::vector <StaticObject*> ()), live_objects(std::vector <LiveObject*> ())  {}

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
    for (auto rit = static_objects.rbegin(); rit != static_objects.rend(); rit++) {
        if ((*rit)->should_be_disposed) {
            auto it = (rit + 1).base();

            delete *it;

            static_objects.erase(it);
        }
    }

    for (auto rit = live_objects.rbegin(); rit != live_objects.rend(); rit++) {
        if ((*rit)->should_be_disposed) {
            auto it = (rit + 1).base();

            delete *it;

            live_objects.erase(it);
        }
    }
}

void fun::Level::Unload() {
    for (auto obj : static_objects) {
        delete obj;
    }

    for (auto obj : live_objects) {
        delete obj;
    }
}

void fun::Level::ShowHierarchy() {
    std::ostringstream mem_addr;

    // mem_addr << this;

    ImGui::Begin(("Level " + name/*mem_addr.str()*/).c_str());

        if (ImGui::TreeNode("Live Objects")) {
            for (auto& object : live_objects) {
                mem_addr.str("");
                mem_addr.clear();
                mem_addr << object;

                ImGui::TableNextColumn();

                if (ImGui::Button(mem_addr.str().c_str(), ImVec2(-FLT_MIN, 0.0f))) {
                    object->should_be_disposed = true;
                }
            }

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Static Objects")) {
            for (auto& object : static_objects) {
                mem_addr.str("");
                mem_addr.clear();
                mem_addr << object;

                ImGui::TableNextColumn();

                if (ImGui::Button(mem_addr.str().c_str(), ImVec2(-FLT_MIN, 0.0f))) {
                    object->should_be_disposed = true;
                }
            }

            ImGui::TreePop();
        }

    ImGui::End();
}

void fun::Level::SetName(const std::string& str) {
    name = str;
}

const std::string& fun::Level::GetName() {
    return name;
}