#include "render/window/window_manager.h"
#include "render/window/window.h"
#include "_time.h"

namespace {
    fun::render::window_t* main_window = nullptr;
}

void fun::render::winmgr::init(const window_data_t& data) {
    ::main_window = new window_t(data);

#if defined(FE2D_IMGUI)
    auto& renderer = ::main_window->get_renderer();

    renderer.resetGLStates();
    ImGui::SFML::Init(renderer);
#endif
}

void fun::render::winmgr::update() {
    ::main_window->poll_events();

#if defined(FE2D_IMGUI)
    ImGui::SFML::Update(::main_window->get_renderer(), fun::time::delta_time_object());
#endif
}

void fun::render::winmgr::close() {
#if defined(FE2D_IMGUI)
    ImGui::SFML::Shutdown();
#endif

    delete ::main_window;
}

fun::render::window_t& fun::render::winmgr::get_main_window() {
    return *::main_window;
}