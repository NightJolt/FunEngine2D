#include "ecs/Level.h"

// fun::Level::Level(const std::string& name) : name(name), static_objects(std::vector <StaticObject*> ()), live_objects(std::vector <LiveObject*> ())  {}

// void fun::Level::Init() {
//     for (auto obj : static_objects) {
//         obj->Init();
//     }

//     for (auto obj : live_objects) {
//         obj->Init();
//     }
// }

// void fun::Level::Update() {
//     for (auto obj : live_objects) {
//         obj->Update();
//     }
// }

// void fun::Level::Dispose() {
//     for (auto rit = static_objects.rbegin(); rit != static_objects.rend(); rit++) {
//         if ((*rit)->should_be_disposed) {
//             auto it = (rit + 1).base();

//             delete *it;

//             static_objects.erase(it);
//         }
//     }

//     for (auto rit = live_objects.rbegin(); rit != live_objects.rend(); rit++) {
//         if ((*rit)->should_be_disposed) {
//             auto it = (rit + 1).base();

//             delete *it;

//             live_objects.erase(it);
//         }
//     }
// }

// void fun::Level::Unload() {
//     for (auto obj : static_objects) {
//         delete obj;
//     }

//     for (auto obj : live_objects) {
//         delete obj;
//     }
// }

// void fun::Level::ShowHierarchy() {

//     ImGui::Begin(("Level " + name).c_str());

//         if (ImGui::TreeNode("Live Objects")) {
//             for (auto object : live_objects) {
//                 ImGui::TableNextColumn();

//                 if (ImGui::Button(object->name.c_str(), ImVec2(-FLT_MIN, 0.0f))) {
//                     object->should_be_disposed = true;
//                 }
//             }

//             ImGui::TreePop();
//         }

//         if (ImGui::TreeNode("Static Objects")) {
//             for (auto object : static_objects) {
//                 ImGui::TableNextColumn();

//                 if (ImGui::Button(object->name.c_str(), ImVec2(-FLT_MIN, 0.0f))) {
//                     object->should_be_disposed = true;
//                 }
//             }

//             ImGui::TreePop();
//         }

//     ImGui::End();
// }