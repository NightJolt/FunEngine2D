#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(sf::Vector2f p) : position(p) {}

ParticleSystem::~ParticleSystem() = default;

void ParticleSystem::Draw(sf::RenderWindow& window) {
    window.draw(&vertices[0], vertices.size(), sf::Points);
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

    for (int i = 0; i < Count(); i++) {
        if (settings.EmitterMass) {
            particles[i].velocity += Math::GravitationalAcceleration(vertices[i].position, position, settings.EmitterMass) * settings.GlobalGravityModifier * FTime::DeltaTime();
        }

        if (settings.ParticlesGravity) {
            for (int j = 0; j < Count(); j++) {
                if (i != j) {
                    particles[i].velocity += Math::GravitationalAcceleration(vertices[i].position, vertices[j].position, particles[j].mass) * settings.GlobalGravityModifier * FTime::DeltaTime();
                }
            }
        }

        if (settings.fade_over_time) {
            vertices[i].color.a = Math::MapValue(particles[i].lifetime, 0, particles[i].init_lifetime, 0, 255);
        }
    }

    for (int i = 0; i < Count(); i++) {
        vertices[i].position += particles[i].velocity * FTime::DeltaTime();
    }
}

void ParticleSystem::Emit(int count) {
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

int ParticleSystem::Count() {
    return particles.size();
}