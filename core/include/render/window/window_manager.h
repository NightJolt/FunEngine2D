#pragma once

#include "../../globals.h"

namespace fun::render::winmgr {
    void init(const window_data_t&);
    void update();
    void close();

    window_t& get_main_window();
}