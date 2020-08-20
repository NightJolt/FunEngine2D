#pragma once

#include <SFML/System.hpp>

using namespace sf;

class FTime {
public:
    static void Recalculate();
    static float DeltaTime();
    static float UnscaledDeltaTime();
    static float TimeElapsed();

    static float time_slow;

private:
    static Clock runtime_clock;
    static Clock delta_clock;

    static float delta_time;
};