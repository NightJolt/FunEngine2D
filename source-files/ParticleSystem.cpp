#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(ParticleSystem::RenderType rt, ParticleSystem::EmissionType et, int c, float t) :
position(sf::Vector2f(0, 0)),
texture(nullptr),
left_to_emit(c),
emission_delay(t),
render_type(rt),
emission_type(et)
{}

void ParticleSystem::Draw(sf::RenderWindow& window) {
    if (render_type == RenderType::Pixel) {
        window.draw(&vertices[0], vertices.size(), sf::Points);
    } else {
        window.draw(&vertices[0], vertices.size(), sf::Quads, sf::RenderStates(texture));
    }
}

void ParticleSystem::Update() {
    if (left_to_emit > 0) {
        if (emission_current_delay <= 0) {
            Emit();

            left_to_emit--;
            emission_current_delay = emission_delay;
        } else {
            emission_current_delay -= FTime::DeltaTime();
        }
    }

    for (int i = 0; i < particles.size(); i++) {
        if (particles[i].lifetime > 0) {
            particles[i].lifetime -= FTime::DeltaTime();

            if (particles[i].lifetime < 0) {
                if (emission_type == EmissionType::Single) {
                    vertices[i].color = sf::Color::Transparent;
                } else {
                    Revive(i);
                }

                if (render_type == RenderType::Sprite) i += 3;
            }
        }
    }

    for (int i = 0; i < particles.size(); i++) {
        if (particles[i].lifetime > 0 && settings.fade_over_time) {
            vertices[i].color.a = Math::MapValue(particles[i].lifetime, 0, particles[i].init_lifetime, 0, 255);
        }
    }

    for (int i = 0; i < particles.size(); i++) {
        if (particles[i].lifetime > 0) {
            vertices[i].position += particles[i].velocity * FTime::DeltaTime();
        }
    }
}

void ParticleSystem::Revive(int i) {
    sf::Vector2f rand_velocity = Math::Normalize(sf::Vector2f((float)Math::Random(-100, 100), (float)Math::Random(-100, 100))) * (float)Math::Random(settings.particle_velocity.x, settings.particle_velocity.y);
    float rand_mass = Math::Random(settings.particle_mass.x, settings.particle_mass.y);

    sf::Vector2f n_position;
    if (settings.emission_radius != 0)
        n_position = position + Math::Normalize(sf::Vector2f((float)Math::Random(-100, 100), (float)Math::Random(-100, 100))) * settings.emission_radius;
    else
        n_position = position;

    if (render_type == RenderType::Pixel) {
        particles[i].lifetime = particles[i].init_lifetime;
        particles[i].mass = rand_mass;
        particles[i].velocity = rand_velocity;

        vertices[i].position = n_position;
    } else {
        sf::FloatRect rand_texture = texture_rects[Math::Random(0, texture_rects.size())];
        float rand_size = Math::Random(settings.sprite_size.x, settings.sprite_size.y);

        for (int j = i; j < i + 4; j++) {
            particles[j].lifetime = particles[i].init_lifetime;
            particles[j].mass = rand_mass;
            particles[j].velocity = rand_velocity;
        }

        vertices[i].position = n_position + sf::Vector2f(-rand_size, -rand_size) * .5f;
        vertices[i].texCoords = sf::Vector2f(rand_texture.left, rand_texture.top);

        vertices[i + 1].position = n_position + sf::Vector2f(rand_size, -rand_size) * .5f;
        vertices[i + 1].texCoords = sf::Vector2f(rand_texture.left + rand_texture.width, rand_texture.top);

        vertices[i + 2].position = n_position + sf::Vector2f(rand_size, rand_size) * .5f;
        vertices[i + 2].texCoords = sf::Vector2f(rand_texture.left + rand_texture.width, rand_texture.top + rand_texture.height);

        vertices[i + 3].position = n_position + sf::Vector2f(-rand_size, rand_size) * .5f;
        vertices[i + 3].texCoords = sf::Vector2f(rand_texture.left, rand_texture.top + rand_texture.height);
    }
}

void ParticleSystem::Emit() {
    float random_lifetime = Math::Random(settings.particle_lifetime.x, settings.particle_lifetime.y);

    if (render_type == RenderType::Pixel) {
        Particle particle(random_lifetime);
        particles.push_back(particle);

        sf::Vertex vertex(position, sf::Color(Math::Random(0, 256), Math::Random(0, 256), Math::Random(0, 256)));
        vertices.push_back(vertex);

        Revive(particles.size() - 1);
    } else {
        Particle particle(random_lifetime);

        particles.push_back(particle);
        particles.push_back(particle);
        particles.push_back(particle);
        particles.push_back(particle);

        sf::Vertex vertex;

        vertices.push_back(vertex);
        vertices.push_back(vertex);
        vertices.push_back(vertex);
        vertices.push_back(vertex);

        Revive(particles.size() - 4);
    }
}

void ParticleSystem::PushTexture(sf::Texture* t) {
    texture = t;
}

void ParticleSystem::PushTextureRect(sf::FloatRect texture_rect) {
    texture_rects.push_back(texture_rect);
}

void ParticleSystem::SetPosition(sf::Vector2f p) {
    position = p;
}

void ParticleSystem::Move(sf::Vector2f p) {
    SetPosition(position + p);
}