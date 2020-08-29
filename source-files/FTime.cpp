#include "FTime.h"

sf::Clock FTime::runtime_clock = sf::Clock();
sf::Clock FTime::delta_clock = sf::Clock();

float FTime::delta_time = 0;
float FTime::time_slow = 1;

std::map <UniqueKey, float> FTime::clocks = std::map <UniqueKey, float> ();

void FTime::Recalculate() {
    delta_time = delta_clock.restart().asSeconds();

    for (auto& clock : clocks) {
        if (clock.second > 0) clock.second -= DeltaTime();
    }
}

float FTime::UnscaledDeltaTime() {
    return delta_time;
}

float FTime::DeltaTime() {
    return UnscaledDeltaTime() / time_slow;
}

float FTime::TimeElapsed() {
    return runtime_clock.getElapsedTime().asSeconds();
}

float FTime::FPS() {
    return 1.f / UnscaledDeltaTime();
}

void FTime::SetTimeSlow(float ts) {
    time_slow = ts;
}

void FTime::SlowerTime(float ts) {
    time_slow *= ts;
}

void FTime::RegisterClock(void* p, std::string k, float v) {
    clocks[UniqueKey(p, std::move(k))] = v;
}

float FTime::RetrieveClock(void* p, std::string k) {
    UniqueKey key = UniqueKey(p, std::move(k));

    if (clocks.contains(key)) return clocks[key];
    else return 0;
}

void FTime::RemoveClock(void* p, std::string k) {
    UniqueKey key = UniqueKey(p, std::move(k));

    if (clocks.contains(key)) clocks.erase(key);
}