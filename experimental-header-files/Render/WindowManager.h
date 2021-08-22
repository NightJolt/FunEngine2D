#pragma once

#include "globals.h"

#include "Render/RenderQueue.h"

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

            void OnResized();
            void Clear(const sf::Color&);
            void Draw();
            void Display();
        };

        static WindowData* main_window;

        static void Init(const std::string&);

    private:
    };
}