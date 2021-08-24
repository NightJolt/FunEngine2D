#include "Render/WindowManager.h"

const sf::Vector2u fun::WindowManager::INIT_SCREEN_SIZE = sf::Vector2u(856, 482);
const sf::Vector2f fun::WindowManager::INIT_VIEW_SIZE = sf::Vector2f(856, 482);
const sf::Vector2f fun::WindowManager::INIT_VIEW_ORIGIN = sf::Vector2f(0, 0);

fun::WindowManager::WindowData* fun::WindowManager::main_window = nullptr;

void fun::WindowManager::Init(const std::string& window_name) {
    main_window = new WindowData(window_name);
}

fun::WindowManager::WindowData::WindowData(const std::string& window_name) :
    window(sf::VideoMode(INIT_SCREEN_SIZE.x, INIT_SCREEN_SIZE.y), window_name),
    world_view(INIT_VIEW_ORIGIN, INIT_VIEW_SIZE),
    ui_view(INIT_VIEW_ORIGIN, INIT_VIEW_SIZE),
    world_queue(RenderQueue()),
    ui_queue(RenderQueue()),
    is_focused(false),
    resolution(INIT_SCREEN_SIZE)
{}

void fun::WindowManager::WindowData::AddWorld(const sf::Drawable& drawable, int order) {
    world_queue.Add(drawable, order);
}

void fun::WindowManager::WindowData::AddUI(const sf::Drawable& drawable, int order) {
    ui_queue.Add(drawable, order);
}

void fun::WindowManager::WindowData::Display(const sf::Color& bg_color) {
    window.clear(bg_color);

    window.setView(world_view);
    window.draw(world_queue);

    window.setView(ui_view);
    window.draw(ui_queue);

    window.display();
}

void fun::WindowManager::WindowData::PollEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();

                break;
            case sf::Event::GainedFocus:
                is_focused = true;

                break;
            case sf::Event::LostFocus:
                is_focused = false;

                break;
            case sf::Event::MouseWheelMoved:
                world_view.zoom(event.mouseWheel.delta > 0 ? 0.9f : 1.1f);

                break;
            case sf::Event::Resized:
                sf::Vector2f ratio = (sf::Vector2f)window.getSize() / (sf::Vector2f)resolution;
                resolution = window.getSize();
                world_view.setSize(world_view.getSize() * ratio);

                //sf::Vector2f scale_val = Math::Sqrt(ratio * Math::Swap(ratio));
                //fps.Rescale(scale_val);

                break;
        }
    }
}