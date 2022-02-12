#include "drawable/Particler.h"

fun::Particler::Particler(RenderType rt, uint32_t max_primitive_count, uint8_t thread_count) : render_type(rt) {
    // thread_pool.resize(thread_count);

    if (render_type == RenderType::Quads) {
        vertices.resize(max_primitive_count * 4);
        particles.resize(max_primitive_count);
    }
}


fun::Particler::~Particler() = default;



// fun::Particler::Particler(Particler&& other) noexcept {
//     transform = other.transform;

//     particles = std::move(other.particles);
//     vertices = std::move(other.vertices);
// }

// fun::Particler& fun::Particler::operator =(Particler&& other) noexcept {
//     if (this == &other) return *this;

//     this->~Particler();

//     transform = other.transform;

//     particles = std::move(other.particles);
//     vertices = std::move(other.vertices);

//     return *this;
// }

void fun::Particler::Emit(uint32_t count, const EmitData& data) {
    if (size == particles.size() || count == 0) return;

    count = std::min((uint32_t)(particles.size() - size), count);
    size_t vertex_index = (size - 1) * 4;

    for (auto particle = particles.begin() + size; particle != particles.begin() + size + count; particle++) {
        particle->position = transform.position;
        particle->direction_angle = fun::math::random_f(data.min_direction_angle, data.max_direction_angle) + transform.rotation;
        particle->body_angle = fun::math::random_f(0, fun::math::constants::double_pi);
        particle->velocity = data.max_velocity_start;
        particle->body_radius = data.max_size_start * fun::math::constants::half_sqrt_2;

        vertex_index += 4;
    }

    size += count;
}

void fun::Particler::Update() {
    UpdateRange(0, size);
}

void fun::Particler::UpdateRange(size_t index, uint32_t count) {
    const float delta_time = fun::time::delta_time();

    size_t vertex_index = index * 4;

    float x;
    float y;

    for (auto particle = particles.begin() + index; particle != particles.begin() + index + count; particle++) {
        particle->position += sf::Vector2(sin(particle->direction_angle), cos(particle->direction_angle)) * particle->velocity * delta_time;

        {
            x = sin(particle->body_angle) * particle->body_radius;
            y = cos(particle->body_angle) * particle->body_radius;

            vertices[vertex_index].position.x = particle->position.x + x;
            vertices[vertex_index].position.y = -(particle->position.y + y);

            vertices[vertex_index].color = sf::Color::Black; // ! check if color step is > 0

            vertex_index += 1;

            vertices[vertex_index].position.x = particle->position.x + y;
            vertices[vertex_index].position.y = -(particle->position.y - x);

            vertices[vertex_index].color = sf::Color::Black;

            vertex_index += 1;

            vertices[vertex_index].position.x = particle->position.x - x;
            vertices[vertex_index].position.y = -(particle->position.y - y);

            vertices[vertex_index].color = sf::Color::Black;

            vertex_index += 1;

            vertices[vertex_index].position.x = particle->position.x - y;
            vertices[vertex_index].position.y = -(particle->position.y + x);

            vertices[vertex_index].color = sf::Color::Black;

            vertex_index += 1;
        }
    }
}

void fun::Particler::draw(sf::RenderTarget& render_target, sf::RenderStates render_states) const {
    if (!size) return;

    render_target.draw(&vertices[0], size * 4, sf::Quads, render_states);
}