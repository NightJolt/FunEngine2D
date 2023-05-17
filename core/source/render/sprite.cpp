#include "render/sprite.h"
#include "_math.h"
#include "tools/debugger.h"

fun::render::sprite_t::sprite_t() :
    m_shader(nullptr), m_update_body(true), m_update_texture(false), m_update_color(false), m_draw_mode(draw_mode_t::normal), m_origin(vec2f_t { .5f, .5f }) {}

void fun::render::sprite_t::bind_texture(const texture_t& texture) {
    m_texture = texture;
    m_primitive.bind_texture(texture);

    select_subtexture(0);
    
    m_update_texture = true;
}

void fun::render::sprite_t::bind_shader(sf::Shader* shader) {
    m_shader = shader;
}

void fun::render::sprite_t::select_subtexture(uint32_t index) {
    auto res = m_texture.get_subtexture(index);

    m_texture_pos = { res[0], res[1] };
    m_texture_size = { res[2], res[3] };

    m_update_texture = true;
}

void fun::render::sprite_t::select_subtexture(vec2u_t pos) {
    auto res = m_texture.get_subtexture(pos);

    m_texture_pos = { res[0], res[1] };
    m_texture_size = { res[2], res[3] };

    m_update_texture = true;
}

void fun::render::sprite_t::select_subtexture(vec2u_t pos, vec2u_t size) {
    m_texture_pos = pos;
    m_texture_size = size;

    m_update_texture = true;
}

fun::vec2f_t fun::render::sprite_t::get_position() const {
    return m_transform.position;
}

void fun::render::sprite_t::set_position(vec2f_t position) {
    m_transform.position = position;
    
    m_update_body = true;
}

void fun::render::sprite_t::move(vec2f_t position) {
    m_transform.position += position;
    
    m_update_body = true;
}

fun::float32_t fun::render::sprite_t::get_rotation() const {
    return math::degrees(m_transform.rotation);
}

void fun::render::sprite_t::set_rotation(float32_t degrees) {
    m_transform.rotation = math::radians(degrees);

    m_update_body = true;
}

void fun::render::sprite_t::rotate(float32_t degrees) {
    m_transform.rotation += math::radians(degrees);
    
    m_update_body = true;
}

fun::vec2f_t fun::render::sprite_t::get_scale() const {
    return m_transform.scale;
}

void fun::render::sprite_t::set_scale(vec2f_t value) {
    m_transform.scale = value;
    
    m_update_body = true;
}

void fun::render::sprite_t::scale(float32_t value) {
    m_transform.scale *= value;
    
    m_update_body = true;
}

void fun::render::sprite_t::scale(vec2f_t value) {
    m_transform.scale *= value;
    
    m_update_body = true;
}

void fun::render::sprite_t::set_origin(vec2f_t origin) {
    m_origin = origin;

    m_update_body = true;
}

void fun::render::sprite_t::set_color(rgba_t color) {
    m_color = color;

    m_update_color = true;
}

void fun::render::sprite_t::set_draw_mode(draw_mode_t draw_mode) {
    m_draw_mode = draw_mode;

    m_update_body = true;
    m_update_texture = true;
}

void fun::render::sprite_t::set_nineslice(float32_t4 borders, float32_t scale) {
    m_nineslice = borders;
    m_nineslice_scale = scale;

    m_update_body = true;
    m_update_texture = true;
}

void fun::render::sprite_t::batch(sprite_t* begin, sprite_t* end) {
    for (sprite_t* sprite = begin; sprite != end; ++sprite) {
        sprite->update();

        m_primitive.batch(sprite->m_primitive);
    }
}

void fun::render::sprite_t::update() const {
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
}

void fun::render::sprite_t::update_body() const {
    m_primitive.set_primitive_type(m_draw_mode == draw_mode_t::normal ? sf::PrimitiveType::Quads : sf::PrimitiveType::TrianglesStrip);

    uint32_t vertice_count = m_draw_mode == draw_mode_t::normal ? 4 : 24;
    if (m_primitive.get_size() != vertice_count) {
        m_primitive.resize(vertice_count);
    }

    vec2f_t position = m_transform.position - m_transform.scale * m_origin;

    if (m_draw_mode == draw_mode_t::normal) {
        vec2f_t ul = position;
        vec2f_t ur = position + vec2f_t { m_transform.scale.x, 0 };
        vec2f_t o = position + m_transform.scale * .5f;

        float32_t value = m_transform.rotation;

        float32_t cv = cosf(m_transform.rotation);
        float32_t sv = sinf(m_transform.rotation);

        vec2f_t nul = { (o.x - ul.x) * cv - (o.y - ul.y) * sv, (o.x - ul.x) * sv + (o.y - ul.y) * cv };
        vec2f_t nur = { (o.x - ur.x) * cv - (o.y - ur.y) * sv, (o.x - ur.x) * sv + (o.y - ur.y) * cv };
        
        m_primitive.get_vertex(0).position = (o - nul).to_sf();
        m_primitive.get_vertex(1).position = (o - nur).to_sf();
        m_primitive.get_vertex(2).position = (o + nul).to_sf();
        m_primitive.get_vertex(3).position = (o + nur).to_sf();
    } else {
        const float32_t4 x_points = {
            position.x,
            position.x + m_nineslice_scale * m_nineslice[0],
            position.x + m_transform.scale.x - m_nineslice_scale * m_nineslice[2],
            position.x + m_transform.scale.x
        };
        
        const float32_t4 y_points = {
            position.y,
            position.y + m_nineslice_scale * m_nineslice[1],
            position.y + m_transform.scale.y - m_nineslice_scale * m_nineslice[3],
            position.y + m_transform.scale.y
        };

        vec2f_t vertex_positions[16];

        for (uint32_t i = 0; i < 4; ++i) {
            for (uint32_t j = 0; j < 4; ++j) {
                vertex_positions[i + j * 4] = vec2f_t { x_points[i], y_points[j] };
            }
        }
        
        for (uint32_t i = 0; i < s_nineslice_vertex_count; ++i) {
            m_primitive.get_vertex(i).position = vertex_positions[s_nineslice_vertex_order[i]].to_sf();
        }
    }
}

void fun::render::sprite_t::update_texture() const {
    if (m_draw_mode == draw_mode_t::normal) {
        m_primitive.get_vertex(0).texCoords = sf::Vector2f(m_texture_pos.x, m_texture_pos.y);
        m_primitive.get_vertex(1).texCoords = sf::Vector2f(m_texture_pos.x + m_texture_size.x, m_texture_pos.y);
        m_primitive.get_vertex(2).texCoords = sf::Vector2f(m_texture_pos.x + m_texture_size.x, m_texture_pos.y + m_texture_size.y);
        m_primitive.get_vertex(3).texCoords = sf::Vector2f(m_texture_pos.x, m_texture_pos.y + m_texture_size.y);
    } else {
        const uint32_t4 x_points = {
            m_texture_pos.x,
            m_texture_pos.x + (uint32_t)(m_texture_size.x * m_nineslice[0]),
            m_texture_pos.x + (uint32_t)(m_texture_size.x * (1 - m_nineslice[2])),
            m_texture_pos.x + m_texture_size.x
        };
        
        const uint32_t4 y_points = {
            m_texture_pos.y,
            uint32_t { m_texture_pos.y + (uint32_t)(m_texture_size.y * m_nineslice[1]) },
            uint32_t { m_texture_pos.y + (uint32_t)(m_texture_size.y * (1 - m_nineslice[3])) },
            m_texture_pos.y + m_texture_size.y
        };

        vec2f_t vertex_texture_coords[16];

        for (uint32_t i = 0; i < 4; ++i) {
            for (uint32_t j = 0; j < 4; ++j) {
                vertex_texture_coords[i + j * 4] = vec2u_t { x_points[i], y_points[j] };
            }
        }
        
        for (uint32_t i = 0; i < s_nineslice_vertex_count; ++i) {
            m_primitive.get_vertex(i).texCoords = vertex_texture_coords[s_nineslice_vertex_order[i]].to_sf();
        }
    }
}

void fun::render::sprite_t::update_color() const {
    auto color = m_color.to_sf();

    for (auto& vertex : m_primitive.get_iterator()) {
        vertex.color = color;
    }
}


void fun::render::sprite_t::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
    update();
    
    render_states.shader = m_shader;

    render_target.draw(m_primitive, render_states);
}