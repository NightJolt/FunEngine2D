#include "FTime.h"

Clock FTime::runtime_clock = Clock();
Clock FTime::delta_clock = Clock();

float FTime::delta_time = 0;
float FTime::time_slow = 1;

void FTime::Recalculate() {
    delta_time = delta_clock.restart().asSeconds();
}

float FTime::DeltaTime() {
    return delta_time / time_slow;
}

float FTime::UnscaledDeltaTime() {
    return delta_time;
}

float FTime::TimeElapsed() {
    return runtime_clock.getElapsedTime().asSeconds();
}