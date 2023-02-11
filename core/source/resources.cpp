#include "resources.h"

static std::unordered_map <std::string, sf::Texture> textures;
static std::unordered_map <std::string, sf::Font> fonts;
// static std::unordered_map <std::string, sf::Image> images;
static std::unordered_map <std::string, sf::Shader*> shaders;

const std::string resources_directory =
#if defined(RELEASE_BUILD)
"/resources/"
#else
"../../resources/"
#endif
;

const std::string textures_directory = resources_directory + "textures/";
const std::string images_directory = resources_directory + "images/";
const std::string fonts_directory = resources_directory + "fonts/";
const std::string shaders_directory = resources_directory + "shaders/";

void fun::resources::load_texture(const std::string& key, const std::string& file) {
    textures.insert_or_assign(key, sf::Texture());

    auto it = textures.find(key);

    assert(it->second.loadFromFile(textures_directory + file));
}

const fun::render::texture_t fun::resources::get_texture(const std::string& key) {
    return render::texture_t(&textures.at(key), { 1, 1 });
}

void fun::resources::load_font(const std::string& key, const std::string& file) {
    fonts.insert_or_assign(key, sf::Font());

    auto it = fonts.find(key);

    assert(it->second.loadFromFile(fonts_directory + file));
}

const sf::Font& fun::resources::get_font(const std::string& key) {
    return fonts.at(key);
}

void fun::resources::load_shader(const std::string& key, const std::string& file) {
    if (shaders.contains(key)) delete shaders[key];

    shaders.emplace(key, new sf::Shader());

    auto it = shaders.find(key);

    it->second->loadFromFile(shaders_directory + file + ".vert", shaders_directory + file + ".frag");
}

sf::Shader* fun::resources::get_shader(const std::string& key) {
    return shaders.at(key);
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
