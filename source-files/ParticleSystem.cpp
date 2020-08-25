#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(sf::Vector2f p) : position(p), texture(nullptr) {}

ParticleSystem::~ParticleSystem() = default;

void ParticleSystem::Draw(sf::RenderWindow& window) {
    window.draw(&vertices[0], vertices.size(), texture ? sf::Quads : sf::Points, sf::RenderStates(texture));
}

void ParticleSystem::Update() {
    for (int i = 0; i < Count(); i++) {
        particles[i].lifetime -= FTime::DeltaTime();

        if (particles[i].lifetime <= 0) {
            particles.erase(particles.begin() + i);
            vertices.erase(vertices.begin() + i);

            i--;
        }
    }

    if (!settings.is_static) {
        for (int i = 0; i < Count(); i++) {
            if (settings.emitter_mass) {
                particles[i].velocity += Math::GravitationalAcceleration(vertices[i].position, position, settings.emitter_mass) * settings.global_gravity_modifier * FTime::DeltaTime();
            }

            if (settings.particles_gravity) {
                for (int j = 0; j < Count(); j++) {
                    if (i != j) {
                        particles[i].velocity += Math::GravitationalAcceleration(vertices[i].position, vertices[j].position, particles[j].mass) * settings.global_gravity_modifier * FTime::DeltaTime();
                    }
                }
            }

            particles[i].velocity += settings.gravity * FTime::DeltaTime();

            if (settings.fade_over_time) {
                vertices[i].color.a = Math::MapValue(particles[i].lifetime, 0, particles[i].init_lifetime, 0, 255);
            }
        }

        for (int i = 0; i < Count(); i++) {
            vertices[i].position += particles[i].velocity * FTime::DeltaTime();
        }
    }
}

void ParticleSystem::Emit(int count) {
    if (texture) {
        EmitSprites(count);
    } else {
        EmitPixels(count);
    }
}

int ParticleSystem::Count() {
    return particles.size();
}

void ParticleSystem::SetPosition(sf::Vector2f p) {
    position = p;
}

void ParticleSystem::Move(sf::Vector2f p) {
    SetPosition(position + p);
}

void ParticleSystem::EmitPixels(int count) {
    for (int i = 0; i < count; i++) {
        Particle particle;
        particle.lifetime = particle.init_lifetime = Math::Random(3, 10);;
        particle.velocity = Math::Normalize(sf::Vector2f((float)Math::Random(-100, 100), (float)Math::Random(-100, 100))) * (float)Math::Random(5, 10);
        particle.mass = Math::Random(1, 20);
        particles.push_back(particle);

        sf::Vertex vertex(position, sf::Color(Math::Random(0, 256), Math::Random(0, 256), Math::Random(0, 256)));
        vertices.push_back(vertex);
    }
}

void ParticleSystem::EmitSprites(int count) {
    for (int i = 0; i < count; i++) {
        sf::FloatRect rand_texture = texture_rects[Math::Random(0, texture_rects.size())];
        float rand_lifetime = Math::Random(3, 10);
        sf::Vector2f rand_velocity = Math::Normalize(sf::Vector2f((float)Math::Random(-100, 100), (float)Math::Random(-100, 100))) * (float)Math::Random(5, 10);
        float rand_mass = Math::Random(1, 20);

        for (int j = 0; j < 4; j++) {
            Particle particle;
            particle.lifetime = particle.init_lifetime = rand_lifetime;
            particle.velocity = rand_velocity;
            particle.mass = rand_mass;
            particles.push_back(particle);
        }

        float rand_size = Math::Random(4, 8);

        sf::Vertex vertex;

        vertex.position = position + sf::Vector2f(-rand_size, -rand_size) * .5f;
        vertex.texCoords = sf::Vector2f(rand_texture.left, rand_texture.top);
        vertices.push_back(vertex);

        vertex.position = position + sf::Vector2f(rand_size, -rand_size) * .5f;
        vertex.texCoords = sf::Vector2f(rand_texture.left + rand_texture.width, rand_texture.top);
        vertices.push_back(vertex);

        vertex.position = position + sf::Vector2f(rand_size, rand_size) * .5f;
        vertex.texCoords = sf::Vector2f(rand_texture.left + rand_texture.width, rand_texture.top + rand_texture.height);
        vertices.push_back(vertex);

        vertex.position = position + sf::Vector2f(-rand_size, rand_size) * .5f;
        vertex.texCoords = sf::Vector2f(rand_texture.left, rand_texture.top + rand_texture.height);
        vertices.push_back(vertex);
    }
}

void ParticleSystem::PushTexture(sf::Texture* t, sf::FloatRect texture_rect) {
    texture = t;
    texture_rects.push_back(texture_rect);
}

void ParticleSystem::ClearTexture() {
    texture = nullptr;
    texture_rects.clear();
}
