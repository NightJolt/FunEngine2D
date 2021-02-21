#include "FTime.h"

sf::Clock FTime::delta_clock = sf::Clock();

float FTime::time_elapsed = 0;
float FTime::unscaled_delta_time = 0;
float FTime::scaled_delta_time = 0;
float FTime::time_scale = 1;
float FTime::fps = 0;

std::map <UniqueKey, float> FTime::clocks = std::map <UniqueKey, float> ();

void FTime::Recalculate() {
    unscaled_delta_time = delta_clock.restart().asSeconds();
    scaled_delta_time = unscaled_delta_time * time_scale;
    time_elapsed += unscaled_delta_time;

    fps = 1.f / unscaled_delta_time;

    for (auto& clock : clocks) {
        if (clock.second > 0) clock.second -= DeltaTime();
    }
}

float FTime::UnscaledDeltaTime() {
    return unscaled_delta_time;
}

float FTime::DeltaTime() {
    return scaled_delta_time;
}

float FTime::TimeElapsed() {
    return time_elapsed;
}

float FTime::FPS() {
    return fps;
}

void FTime::SetTimeScale(float val) {
    time_scale = val;
}

void FTime::GetTimeScale(float val) {
    time_scale *= val;
}

void FTime::RegisterClock(void* ptr, const std::string& str, float val) {
    clocks[UniqueKey(ptr, str.c_str())] = val;
}

float FTime::RetrieveClock(void* ptr, const std::string& str) {
    UniqueKey key = UniqueKey(ptr, str.c_str());

    return clocks[key];
}

void FTime::RemoveClock(void* p, const std::string& k) {
    UniqueKey key = UniqueKey(p, k.c_str());

    clocks.erase(key);
}