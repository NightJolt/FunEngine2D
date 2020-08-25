#pragma once

#include "SFML/Graphics.hpp"

#include <vector>

#include "Math.h"
#include "FTime.h"

#include <iostream>

class ParticleSystem {
public:
    enum RenderType {
        Pixel,
        Sprite
    };

    struct Settings {
        Settings() : GlobalGravityModifier(1), EmitterMass(0), ParticlesGravity(false), fade_over_time(true) {}

        float GlobalGravityModifier;
        float EmitterMass;
        bool ParticlesGravity;

        bool fade_over_time;
    };

    explicit ParticleSystem(sf::Vector2f = sf::Vector2f(0, 0));
    ~ParticleSystem();

    struct Particle {
        Particle() : lifetime(0), velocity(sf::Vector2f(0, 0)), mass(1) {}
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

    Settings settings;

private:

    sf::Clock time_elapsed;
    sf::Vector2f position;

    std::vector <Particle> particles;
    std::vector <sf::Vertex> vertices;
};