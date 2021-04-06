#include "R.h"

const std::string fun::R::resources_directory = "../R/";
const std::string fun::R::textures_directory = R::resources_directory + "textures/";
const std::string fun::R::fonts_directory = R::resources_directory + "fonts/";
const std::string fun::R::shaders_directory = R::resources_directory + "shaders/";

std::vector <sf::Texture> fun::R::textures = std::vector <sf::Texture> ();
const std::string fun::R::textures_to_load[] = {
};

std::vector <sf::Font> fun::R::fonts = std::vector <sf::Font> ();
const std::string fun::R::fonts_to_load[] = {
};

std::vector <sf::Shader*> fun::R::shaders = std::vector <sf::Shader*> ();
const std::string fun::R::shaders_to_load[] = {
};

void fun::R::LoadResources() {
    for (const auto& texture_path : textures_to_load) {
        sf::Texture* texture = &textures.emplace_back(sf::Texture());

        if (!texture->loadFromFile(textures_directory + texture_path)) {
            textures.pop_back();
        }
    }

    for (const auto& font_path : fonts_to_load) {
        sf::Font* font = &fonts.emplace_back(sf::Font());

        if (!font->loadFromFile(fonts_directory + font_path)) {
            fonts.pop_back();
        }
    }

    for (const auto& shader_path : shaders_to_load) {
        sf::Shader* shader = shaders.emplace_back(new sf::Shader());

        if (!shader->loadFromFile(shaders_directory + shader_path + ".vert", shaders_directory + shader_path + ".frag")) {
            shaders.pop_back();
        }
    }
}