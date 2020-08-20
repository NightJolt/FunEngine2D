#include "R.h"

const std::string R::resources_directory = "../R/";
const std::string R::textures_directory = R::resources_directory + "textures/";
const std::string R::fonts_directory = R::resources_directory + "fonts/";
const std::string R::shaders_directory = R::resources_directory + "shaders/";

std::vector <sf::Texture> R::textures = std::vector <sf::Texture> ();
const std::string R::textures_to_load[] = {
        "test.png"
};

std::vector <sf::Font> R::fonts = std::vector <sf::Font> ();
const std::string R::fonts_to_load[] = {
        "andy_bold.ttf"
};

void R::LoadResources() {
    for (const auto& texture_path : textures_to_load) {
        sf::Texture* c_texture = &textures.emplace_back(sf::Texture());

        if (!c_texture->loadFromFile(textures_directory + texture_path)) {
            textures.pop_back();
        }
    }

    for (const auto& font_path : fonts_to_load) {
        sf::Font* c_font = &fonts.emplace_back(sf::Font());

        if (!c_font->loadFromFile(fonts_directory + font_path)) {
            fonts.pop_back();
        }
    }
}