#pragma once

#include <SFML/System.hpp>

class FTime {
public:
    static void Recalculate();
    static float UnscaledDeltaTime();
    static float DeltaTime();
    static float TimeElapsed();
    static float FPS();

    static float time_slow;

private:
    static sf::Clock runtime_clock;
    static sf::Clock delta_clock;

    static float delta_time;
};