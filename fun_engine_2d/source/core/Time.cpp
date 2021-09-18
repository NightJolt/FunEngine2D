#include "../../include/core/Time.h"

sf::Clock fun::Time::delta_clock = sf::Clock();

float fun::Time::time_elapsed = 0;
float fun::Time::unscaled_delta_time = 0;
float fun::Time::scaled_delta_time = 0;
float fun::Time::time_scale = 1;
float fun::Time::fps = 0;

std::map <UniqueKey, float> fun::Time::clocks = std::map <UniqueKey, float> ();

void fun::Time::Recalculate() {
    unscaled_delta_time = delta_clock.restart().asSeconds();
    scaled_delta_time = unscaled_delta_time * time_scale;
    time_elapsed += unscaled_delta_time;

    fps = 1.f / unscaled_delta_time;

    for (auto& clock : clocks) {
        if (clock.second > 0) clock.second -= DeltaTime();
    }
}

float fun::Time::UnscaledDeltaTime() {
    return unscaled_delta_time;
}

float fun::Time::DeltaTime() {
    return scaled_delta_time;
}

float fun::Time::TimeElapsed() {
    return time_elapsed;
}

float fun::Time::FPS() {
    return fps;
}

void fun::Time::SetTimeScale(float val) {
    time_scale = val;
}

void fun::Time::GetTimeScale(float val) {
    time_scale *= val;
}

void fun::Time::RegisterClock(void* ptr, const std::string& str, float val) {
    clocks[UniqueKey(ptr, str.c_str())] = val;
}

float fun::Time::RetrieveClock(void* ptr, const std::string& str) {
    UniqueKey key = UniqueKey(ptr, str.c_str());

    return clocks[key];
}

void fun::Time::RemoveClock(void* p, const std::string& k) {
    UniqueKey key = UniqueKey(p, k.c_str());

    clocks.erase(key);
}