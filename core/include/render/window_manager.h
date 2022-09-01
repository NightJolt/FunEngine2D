#pragma once

#include "../globals.h"
#include "../_math.h"
#include "../tools/debugger.h"
#include "../_time.h"
#include "render_queue.h"

namespace fun::winmgr {
    struct window_data_t {
        explicit window_data_t(const std::string& = "unnamed", const vec2u_t = { 856, 482 }, fun::mask32_t = sf::Style::Default, const sf::ContextSettings& = sf::ContextSettings());

        std::string name;
        vec2u_t size;
        fun::mask32_t style;
        sf::ContextSettings settings;
    };

    struct window_t {
        sf::RenderWindow render;

        // render queues
        render_queue_t world_queue;
        render_queue_t ui_queue;

        // render views
        sf::View world_view;
        vec2f_t world_view_size;

        sf::View ui_view;
        sf::View final_view;

        // render textures
        sf::RenderTexture world_buffer;
        sf::RenderTexture ui_buffer;
        sf::RenderTexture final_buffer;

        // render sprites
        sf::Sprite world_render;
        sf::Sprite ui_render;
        sf::Sprite final_render;

        bool is_focused;
        float zoom;

        explicit window_t(const window_data_t&);

        void refresh_window();

        void target_framerate(uint32_t);
        void set_vsync(bool);

        void set_world_view(vec2f_t, float);
        // void set_zoom(float);
        // void set_zoom_limits(float, float);

        void draw_world(const sf::Drawable&, layer_t, const sf::RenderStates& = sf::RenderStates::Default);
        void draw_ui(const sf::Drawable&, layer_t, const sf::RenderStates& = sf::RenderStates::Default);

        void poll_events();
        void display(const sf::Color&, const sf::Shader* = nullptr);

        vec2i_t get_mouse_screen_position();
        vec2f_t get_mouse_world_position();

        vec2f_t screen_to_world(const vec2i_t);
        vec2i_t world_to_screen(const vec2f_t);
    };

    extern window_t* main_window;

    void init(const window_data_t&);
    void update();
    void close();
}