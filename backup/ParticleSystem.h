#pragma once

#include "SFML/Graphics.hpp"

#include "../Core/Math.h"
#include "../Core/Time.h"

#include <iostream>

class ParticleSystem {
public:
    enum RenderType { Pixel, Sprite };
    enum EmissionType { Single, Loop };

    struct Settings {
        Settings() :
        particle_velocity(sf::Vector2f(50, 100)),
        particle_lifetime(sf::Vector2f(20, 50)),
        particle_mass(sf::Vector2f(2, 5)),
        sprite_size(sf::Vector2f(30, 50)),
        emission_radius(0),
        gravity(sf::Vector2f(0, 0)),
        fade_over_time(true)
        {}

        sf::Vector2f particle_velocity;
        sf::Vector2f particle_lifetime;
        sf::Vector2f particle_mass;
        sf::Vector2f sprite_size;
        float emission_radius;

        sf::Vector2f position;
        sf::Vector2f gravity;
        bool fade_over_time;
    };

    explicit ParticleSystem(RenderType, EmissionType, int, float);

    struct Particle {
        explicit Particle(float t, sf::Vector2f v = sf::Vector2f(0, 0), float m = 1) : velocity(v), mass(m), init_lifetime(t) {}

        float lifetime;
        float init_lifetime;
        sf::Vector2f velocity;
        float mass;
    };

    void Draw(sf::RenderWindow&);
    void Update();

    void PushTexture(sf::Texture*);
    void PushTextureRect(sf::FloatRect);

    void SetPosition(sf::Vector2f);
    void Move(sf::Vector2f);

    Settings settings;

private:
    void Revive(int);
    void Emit();

    int left_to_emit;
    float emission_delay;
    float emission_current_delay;

    sf::Vector2f position;

    RenderType render_type;
    EmissionType emission_type;

    std::vector <Particle> particles;
    std::vector <sf::Vertex> vertices;

    sf::Texture* texture;
    std::vector <sf::FloatRect> texture_rects;
};