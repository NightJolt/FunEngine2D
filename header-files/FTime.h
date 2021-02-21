#pragma once

#include "globals.h"

class FTime {
public:
    static void Recalculate();
    static float UnscaledDeltaTime();
    static float DeltaTime();
    static float TimeElapsed();
    static float FPS();

    static void SetTimeScale(float);
    static void GetTimeScale(float);

    static void RegisterClock(void*, const std::string&, float);
    static float RetrieveClock(void*, const std::string&);
    static void RemoveClock(void*, const std::string&);

private:
    static sf::Clock delta_clock;

    static float time_elapsed;
    static float unscaled_delta_time;
    static float scaled_delta_time;
    static float time_scale;
    static float fps;

    static std::map <UniqueKey, float> clocks;
};