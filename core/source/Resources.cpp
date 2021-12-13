#include "Resources.h"

void fun::resources::load_texture(const std::string& key, const std::string& file) {
    textures.insert_or_assign(key, sf::Texture());

    auto it = textures.find(key);

    if (!it->second.loadFromFile(textures_directory + file)) {
        textures.erase(it);
    }
}

const sf::Texture& fun::resources::get_texture(const std::string& key) {
    return textures.at(key);
}

void fun::resources::load_font(const std::string& key, const std::string& file) {
    fonts.insert_or_assign(key, sf::Font());

    auto it = fonts.find(key);

    if (!it->second.loadFromFile(fonts_directory + file)) {
        fonts.erase(it);
    }
}

const sf::Font& fun::resources::get_font(const std::string& key) {
    return fonts.at(key);
}

// void LoadResources() {
    // for (const auto& texture_path : textures_to_load) {
    //     sf::Texture* texture = &textures.emplace_back(sf::Texture());

    //     if (!texture->loadFromFile(textures_directory + texture_path)) {
    //         textures.pop_back();
    //     }
    // }

    // for (const auto& image_path : images_to_load) {
    //     sf::Image* image = &images.emplace_back(sf::Image());

    //     if (!image->loadFromFile(images_directory + image_path)) {
    //         images.pop_back();
    //     }
    // }

    // for (const auto& shader_path : shaders_to_load) {
    //     sf::Shader* shader = shaders.emplace_back(new sf::Shader());

    //     if (!shader->loadFromFile(shaders_directory + shader_path + ".vert", shaders_directory + shader_path + ".frag")) {
    //         shaders.pop_back();
    //     }
    // }
// }