#pragma once

#include "../globals.h"

#include "RenderQueue.h"
#include "../Math.h"

namespace fun {
    class WindowManager {
    public:

        static const sf::Vector2u INIT_SCREEN_SIZE;
        static const sf::Vector2f INIT_VIEW_SIZE;
        static const sf::Vector2f INIT_VIEW_ORIGIN;

        struct WindowData {
            explicit WindowData(const std::string&);

            sf::RenderWindow window;

            sf::View world_view;
            sf::View ui_view;

            RenderQueue world_queue;
            RenderQueue ui_queue;

            bool is_focused;
            sf::Vector2u resolution;

            void AddWorld(const sf::Drawable&, int);
            void AddUI(const sf::Drawable&, int);

            void PollEvents();
            void Display(const sf::Color&);
        };

        static WindowData* main_window;

        static void Init(const std::string&);

    private:
    };
}