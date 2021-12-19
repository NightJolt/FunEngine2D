#pragma once

#include "../globals.h"

#include "RenderQueue.h"
#include "../_Math.h"
#include "../tools/Debugger.h"

namespace fun::wndmgr {
    struct WindowData {
        explicit WindowData(const std::string& = "unnamed", const sf::Vector2u& = { 856, 482 }, u32 = sf::Style::Default, const sf::ContextSettings& = sf::ContextSettings());

        std::string name;
        sf::Vector2u size;
        u32 style;
        sf::ContextSettings settings;
    };

    struct Window {
        sf::RenderWindow render_window;

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
        // sf::Vector2u resolution;

        explicit Window(const WindowData&);

        void RefreshWindow();

        void AddWorld(const sf::Drawable&, int);
        void AddUI(const sf::Drawable&, int);

        void PollEvents();
        void Display(const sf::Color&);

        sf::Vector2i GetMouseScreenPosition();
        sf::Vector2f GetMouseWorldPosition();

        sf::Vector2f ScreenToWorld(const sf::Vector2i&);
        sf::Vector2i WorldToScreen(const sf::Vector2f&);
    };

    extern Window* main_window;

    void init(const WindowData&);
}