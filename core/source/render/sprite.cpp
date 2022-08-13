#include "render/sprite.h"

fun::sprite_t::sprite_t() : m_shader(nullptr), m_update_body(false), m_update_texture(false), m_update_color(false) {
    m_primitive.set_primitive_type(sf::PrimitiveType::Quads);
    m_primitive.get_vertices().resize(4);
}



void fun::sprite_t::bind_texture(const texture_t& texture) {
    m_texture = texture;

    m_update_texture = true;
}

void fun::sprite_t::bind_shader(sf::Shader* shader) {
    m_shader = shader;
}



void fun::sprite_t::select_subtexture(uint32_t index) {
    auto res = m_texture.get_subtexture(index);

    m_texture_pos = { res[0], res[1] };
    m_texture_size = { res[2], res[3] };

    m_update_texture = true;
}

void fun::sprite_t::select_subtexture(vec2u_t pos, vec2u_t size) {
    m_texture_pos = pos;
    m_texture_size = size;

    m_update_texture = true;
}

void fun::sprite_t::set_position(vec2f_t position) {
    m_transform.position = position;
    
    m_update_body = true;
}

void fun::sprite_t::move(vec2f_t position) {
    m_transform.position += position;
    
    m_update_body = true;
}

void fun::sprite_t::set_rotation(float degrees) {
    m_transform.rotation = math::radians(degrees);

    m_update_body = true;
}

void fun::sprite_t::rotate(float degrees) {
    m_transform.rotation += math::radians(degrees);
    
    m_update_body = true;
}

void fun::sprite_t::set_scale(vec2f_t value) {
    m_transform.scale = value;
    
    m_update_body = true;
}

void fun::sprite_t::scale(float value) {
    m_transform.scale *= value;
    
    m_update_body = true;
}

void fun::sprite_t::scale(vec2f_t value) {
    m_transform.scale *= value;
    
    m_update_body = true;
}

void fun::sprite_t::set_origin(vec2f_t origin) {
    m_origin = origin;

    m_update_body = true;
}

void fun::sprite_t::set_color(rgba_t color) {
    m_color = color;

    m_update_color = true;
}




void fun::sprite_t::update_body() const {
    auto& vertices = m_primitive.get_vertices();

    vec2f_t position = m_transform.position - m_transform.scale * m_origin;

    vec2f_t ul = position;
    vec2f_t ur = position + vec2f_t { m_transform.scale.x, 0 };
    vec2f_t o = position + m_transform.scale * .5f;

    float value = m_transform.rotation;

    float cv = cosf(m_transform.rotation);
    float sv = sinf(m_transform.rotation);

    vec2f_t nul = { (o.x - ul.x) * cv - (o.y - ul.y) * sv, (o.x - ul.x) * sv + (o.y - ul.y) * cv };
    vec2f_t nur = { (o.x - ur.x) * cv - (o.y - ur.y) * sv, (o.x - ur.x) * sv + (o.y - ur.y) * cv };
    
    vertices[0].position = (o - nul).to_sf();
    vertices[1].position = (o - nur).to_sf();
    vertices[2].position = (o + nul).to_sf();
    vertices[3].position = (o + nur).to_sf();
}

void fun::sprite_t::update_texture() const {
    auto& vertices = m_primitive.get_vertices();
    
    vertices[0].texCoords = sf::Vector2f(m_texture_pos.x, m_texture_pos.y);
    vertices[1].texCoords = sf::Vector2f(m_texture_pos.x + m_texture_size.x, m_texture_pos.y);
    vertices[2].texCoords = sf::Vector2f(m_texture_pos.x + m_texture_size.x, m_texture_pos.y + m_texture_size.y);
    vertices[3].texCoords = sf::Vector2f(m_texture_pos.x, m_texture_pos.y + m_texture_size.y);
}

void fun::sprite_t::update_color() const {
    auto& vertices = m_primitive.get_vertices();
    auto color = m_color.to_sf();
    
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
}


void fun::sprite_t::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
    if (m_update_body) {
        update_body();

        m_update_body = false;
    }

    if (m_update_texture) {
        update_texture();

        m_update_texture = false;
    }

    if (m_update_color) {
        update_color();

        m_update_color = false;
    }

    render_states.texture = m_texture.get_texture();
    render_states.shader = m_shader;

    render_target.draw(m_primitive, render_states);
}