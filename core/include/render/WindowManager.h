#pragma once

#include "../Globals.h"
#include "RenderQueue.h"
#include "../_Math.h"
#include "../tools/Debugger.h"
#include "../_Time.h"

namespace fun::wndmgr {
    struct WindowData {
        explicit WindowData(const std::string& = "unnamed", const vec2u_t = { 856, 482 }, fun::mask32_t = sf::Style::Default, const sf::ContextSettings& = sf::ContextSettings());

        std::string name;
        vec2u_t size;
        fun::mask32_t style;
        sf::ContextSettings settings;
    };

    struct Window {
        sf::RenderWindow render;

        // render queues
        RenderQueue world_queue;
        RenderQueue ui_queue;

        // render views
        sf::View world_view;
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

        explicit Window(const WindowData&);

        void RefreshWindow();

        void DrawWorld(const sf::Drawable&, int);
        void DrawUI(const sf::Drawable&, int);

        void PollEvents();
        void Display(const sf::Color&, const sf::Shader* = nullptr);

        vec2i_t GetMouseScreenPosition();
        vec2f_t GetMouseWorldPosition();

        vec2f_t ScreenToWorld(const vec2i_t&);
        vec2i_t WorldToScreen(const vec2f_t&);
    };

    extern Window* main_window;

    void init(const WindowData&);
    void update();
    void close();
}