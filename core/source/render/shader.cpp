#include "render/shader.h"

fun::render::shader_t::shader_t(sf::Shader* shader) :
    m_shader(shader)
{}

void fun::render::shader_t::set_shader(sf::Shader* shader) {
    m_shader = shader;
}

sf::Shader* fun::render::shader_t::get_shader() const {
    return m_shader;
}