#pragma once

#include <SFML/System.hpp>

#include <map>

#include "globals.h"

class FTime {
public:
    static void Recalculate();
    static float UnscaledDeltaTime();
    static float DeltaTime();
    static float TimeElapsed();
    static float FPS();

    static void SetTimeSlow(float);
    static void SlowerTime(float);

    static void RegisterClock(void*, std::string, float);
    static float RetrieveClock(void*, std::string);
    static void RemoveClock(void*, std::string);

private:
    static sf::Clock runtime_clock;
    static sf::Clock delta_clock;

    static float delta_time;
    static float time_slow;

    static std::map <UniqueKey, float> clocks;
};