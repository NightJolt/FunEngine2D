#pragma once

#include "globals.h"

namespace fun::resources {
    void load_texture(const std::string&, const std::string&);
    const sf::Texture& get_texture(const std::string&);

    // void LoadImage(const std::string&, const std::string&);
    // const sf::Image& GetImage(const std::string&);

    void load_font(const std::string&, const std::string&);
    const sf::Font& get_font(const std::string&);

    void load_shader(const std::string&, const std::string&);
    const sf::Shader* get_shader(const std::string&);

    // todo: audio
    // todo: lua scripts

    static std::unordered_map <std::string, sf::Texture> textures;
    static std::unordered_map <std::string, sf::Font> fonts;
    // static std::unordered_map <std::string, sf::Image> images;
    static std::unordered_map <std::string, sf::Shader*> shaders;

    const std::string resources_directory =
    #if defined(RELEASE_BUILD)
    "/resources/"
    #else
    "../resources/"
    #endif
    ;

    const std::string textures_directory = resources_directory + "textures/";
    const std::string images_directory = resources_directory + "images/";
    const std::string fonts_directory = resources_directory + "fonts/";
    const std::string shaders_directory = resources_directory + "shaders/";
}