#pragma once

#include "Globals.h"

namespace fun::resources {
    void load_texture(const std::string&, const std::string&);
    const sf::Texture& get_texture(const std::string&);

    // void LoadImage(const std::string&, const std::string&);
    // const sf::Image& GetImage(const std::string&);

    void load_font(const std::string&, const std::string&);
    const sf::Font& get_font(const std::string&);

    void load_shader(const std::string&, const std::string&);
    sf::Shader* get_shader(const std::string&);

    // todo: audio
    // todo: lua scripts
    ;
}