#pragma once

#include "../globals.h"

#include "RenderQueue.h"
#include "../_Math.h"
#include "../tools/Debugger.h"

namespace fun::wndmgr {
        extern const sf::Vector2u INIT_SCREEN_SIZE;
        extern const sf::Vector2f INIT_VIEW_SIZE;
        extern const sf::Vector2f INIT_VIEW_ORIGIN;

        struct WindowData {
            explicit WindowData(const std::string&, i32, const sf::ContextSettings&);

            sf::RenderWindow window;

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
            sf::Vector2u resolution;

            void AddWorld(const sf::Drawable&, int);
            void AddUI(const sf::Drawable&, int);

            void PollEvents();
            void Display(const sf::Color&);

            sf::Vector2i GetMouseScreenPosition();
            sf::Vector2f GetMouseWorldPosition();

            sf::Vector2f ScreenToWorld(const sf::Vector2i&);
            sf::Vector2i WorldToScreen(const sf::Vector2f&);
        };

        extern WindowData* main_window;

        void init(const std::string&, i32 = sf::Style::Default, const sf::ContextSettings& = sf::ContextSettings());
}