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

void fun::WindowManager::WindowData::OnResized() {}

void fun::WindowManager::WindowData::Clear(const sf::Color& color) {
    window.clear(color);
}

void fun::WindowManager::WindowData::Draw() {
    window.setView(world_view);
    window.draw(world_queue);

    window.setView(ui_view);
    window.draw(ui_queue);
}

void fun::WindowManager::WindowData::Display() {
    window.display();
}
