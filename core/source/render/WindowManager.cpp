#include "render/WindowManager.h"

fun::wndmgr::Window* fun::wndmgr::main_window = nullptr;

fun::wndmgr::WindowData::WindowData(const std::string& name, const sf::Vector2u& size, u32 style, const sf::ContextSettings& settings) :
    name(name),
    size(size),
    style(style),
    settings(settings)
{   
}

void fun::wndmgr::init(const WindowData& data) {
    main_window = new Window(data);
}

fun::wndmgr::Window::Window(const WindowData& data) :
    render_window(sf::VideoMode(data.size.x, data.size.y), data.name, data.style, data.settings),
    is_focused(false),
    zoom(1)
{
    RefreshWindow();

    world_view.setCenter(0, 0);
}

void fun::wndmgr::Window::RefreshWindow() {
    const sf::Vector2u& new_resolution = render_window.getSize();

    world_buffer.create(new_resolution.x, new_resolution.y, render_window.getSettings());
    world_view.setSize((sf::Vector2f)new_resolution);
    world_view.zoom(zoom);
    world_render.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)new_resolution));

    final_view.setSize((sf::Vector2f)new_resolution);
    final_view.setCenter((sf::Vector2f)new_resolution * .5f);
}

void fun::wndmgr::Window::DrawWorld(const sf::Drawable& drawable, int order) {
    world_queue.Add(drawable, order);
}

void fun::wndmgr::Window::DrawUI(const sf::Drawable& drawable, int order) {
    ui_queue.Add(drawable, order);
}

void fun::wndmgr::Window::Display(const sf::Color& bg_color) {
    world_buffer.clear(bg_color);

    world_buffer.setView(world_view);
    world_buffer.draw(world_queue);
    world_buffer.display();

    world_render.setTexture(world_buffer.getTexture());

    render_window.setView(final_view);
    render_window.draw(world_render/*, fun::R::shaders[0]*/);

#if defined(USES_IMGUI)
    ImGui::SFML::Render(render_window);
#endif

    render_window.display();

    world_queue.Clear();
}

void fun::wndmgr::Window::PollEvents() {
    sf::Event event;

    float curr_zoom_value;

    while (render_window.pollEvent(event)) {
#if defined(USES_IMGUI)
        ImGui::SFML::ProcessEvent(event);
#endif
        switch (event.type) {
            case sf::Event::Closed:
                render_window.close();

                break;
            case sf::Event::GainedFocus:
                is_focused = true;

                break;
            case sf::Event::LostFocus:
                is_focused = false;

                break;
            case sf::Event::MouseWheelMoved:
                curr_zoom_value = event.mouseWheel.delta > 0 ? .9f : 1.1f;

                zoom *= curr_zoom_value;

                world_view.zoom(curr_zoom_value);

                break;
            case sf::Event::Resized:
                RefreshWindow();

                // ? FOR UI
                // sf::Vector2f scale_val = Math::Sqrt(ratio * Math::Swap(ratio));
                // fps.Rescale(scale_val);

                break;
        }
    }
}

sf::Vector2i fun::wndmgr::Window::GetMouseScreenPosition() {
    return sf::Mouse::getPosition(render_window);
}

sf::Vector2f fun::wndmgr::Window::GetMouseWorldPosition() {
    return ScreenToWorld(GetMouseScreenPosition());
}

sf::Vector2f fun::wndmgr::Window::ScreenToWorld(const sf::Vector2i& p) {
    world_buffer.setView(world_view);

    return world_buffer.mapPixelToCoords(p);
}

sf::Vector2i fun::wndmgr::Window::WorldToScreen(const sf::Vector2f& p) {
    world_buffer.setView(world_view);

    return world_buffer.mapCoordsToPixel(p);
}
