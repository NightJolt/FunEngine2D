#include "FTime.h"

sf::Clock FTime::runtime_clock = sf::Clock();
sf::Clock FTime::delta_clock = sf::Clock();

float FTime::delta_time = 0;
float FTime::time_slow = 1;

void FTime::Recalculate() {
    delta_time = delta_clock.restart().asSeconds();
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
