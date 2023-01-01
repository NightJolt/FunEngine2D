#pragma once

#include "../../globals.h"
#include "../../vec2.h"
#include "../render_queue.h"
#include "../../color.h"

namespace fun::render {
    class window_t {
    public:
        explicit window_t(const window_data_t&);

        void refresh_window();

        bool is_open() const;
        bool is_focused() const;
        float get_zoom() const;
        void zoom(float);
        void zoom_into(vec2f_t, float);
        sf::RenderWindow& get_renderer();

        void target_framerate(uint32_t);
        void set_vsync(bool);

        void set_world_view(vec2f_t, float);
        void move_world_view(vec2f_t);

        void draw_world(const sf::Drawable&, layer_t, const sf::RenderStates& = sf::RenderStates::Default);
        void draw_ui(const sf::Drawable&, layer_t, const sf::RenderStates& = sf::RenderStates::Default);

        void register_event_handler(sf::Event::EventType, std::function<void(window_t&, const sf::Event&)>);

        void update();
        void display(const rgb_t&, const sf::Shader* = nullptr);

        vec2i_t get_mouse_screen_position();
        vec2f_t get_mouse_world_position();

        vec2f_t screen_to_world(const vec2i_t);
        vec2i_t world_to_screen(const vec2f_t);

        void set_cursor_visible(bool);
        void set_cursor_grabbed(bool);

    private:
        bool m_is_focused;
        float m_zoom;

        sf::RenderWindow renderer;

        // render queues
        render_queue_t world_queue;
        render_queue_t ui_queue;

        // render views
        sf::View world_view;
        float view_height;

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

        std::optional <std::function<void(window_t&, const sf::Event&)>> m_event_handlers[sf::Event::EventType::Count];
    };
}