#pragma once

#include "SFML/Graphics.hpp"

#include <vector>

#include "Math.h"
#include "FTime.h"

#include <iostream>

class ParticleSystem {
public:
    struct Settings {
        Settings() : is_static(false), global_gravity_modifier(1), emitter_mass(0), particles_gravity(false), fade_over_time(true), gravity(sf::Vector2f(0, 0)) {}

        bool is_static;
        float global_gravity_modifier;
        float emitter_mass;
        bool particles_gravity;
        bool fade_over_time;
        sf::Vector2f gravity;
    };

    explicit ParticleSystem(sf::Vector2f = sf::Vector2f(0, 0));
    ~ParticleSystem();

    struct Particle {
        Particle() : lifetime(0), init_lifetime(0), velocity(sf::Vector2f(0, 0)), mass(1) {}
        ~Particle() = default;

        float lifetime;
        float init_lifetime;
        sf::Vector2f velocity;
        float mass;
    };

    void Draw(sf::RenderWindow&);
    void Update();
    void Emit(int);
    int Count();
    void SetPosition(sf::Vector2f);
    void Move(sf::Vector2f);
    void PushTexture(sf::Texture*, sf::FloatRect);
    void ClearTexture();

    Settings settings;

    sf::Texture* texture;
    std::vector <sf::FloatRect> texture_rects;

private:
    void EmitPixels(int);
    void EmitSprites(int);

    sf::Clock time_elapsed;
    sf::Vector2f position;

    std::vector <Particle> particles;
    std::vector <sf::Vertex> vertices;
};