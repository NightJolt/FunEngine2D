#include "render/window/window_data.h"

fun::render::window_data_t::window_data_t(const std::string& name, const vec2u_t size, fun::mask32_t style, const sf::ContextSettings& settings) :
    name(name),
    size(size),
    style(style),
    settings(settings)
{
    if (style == sf::Style::Fullscreen) {
        auto& video_mode = sf::VideoMode::getFullscreenModes().front();
        this->size = { video_mode.width, video_mode.height };
    }
}