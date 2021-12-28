#pragma once

#include "globals.h"

namespace fun::time {
    void recalculate();
    float unscaled_delta_time();
    float delta_time();
    sf::Time delta_time_object();
    float time_elapsed();
    float fps();

    void set_time_scale(float);
    void get_time_scale(float);

    void register_clock(const UniqueKey&, float);
    float get_clock(const UniqueKey&);
    void remove_clock(const UniqueKey&);
}