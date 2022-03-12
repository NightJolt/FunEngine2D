#include "render/WindowManager.h"

fun::wndmgr::Window* fun::wndmgr::main_window = nullptr;

fun::wndmgr::WindowData::WindowData(const std::string& name, const vec2u_t size, fun::mask32_t style, const sf::ContextSettings& settings) :
    name(name),
    size(size),
    style(style),
    settings(settings)
{   
}

void fun::wndmgr::init(const WindowData& data) {
    main_window = new Window(data);

    main_window->render.setFramerateLimit(60);
    main_window->render.setVerticalSyncEnabled(false);

#if defined(USES_IMGUI)
    main_window->render.resetGLStates();

    ImGui::SFML::Init(main_window->render);
#endif
}

void fun::wndmgr::update() {
    main_window->PollEvents();

#if defined(USES_IMGUI)
    ImGui::SFML::Update(main_window->render, fun::time::delta_time_object());
#endif
}

void fun::wndmgr::close() {
#if defined(USES_IMGUI)
    ImGui::SFML::Shutdown();
#endif

    delete main_window;
}

fun::wndmgr::Window::Window(const WindowData& data) :
    render(sf::VideoMode(data.size.x, data.size.y), data.name, data.style, data.settings),
    is_focused(false),
    zoom(1)
{
    RefreshWindow();

    world_view.setCenter(0, 0);
}

void fun::wndmgr::Window::RefreshWindow() {
    const vec2u_t& new_resolution = render.getSize();

    world_buffer.create(new_resolution.x, new_resolution.y, render.getSettings());
    world_view.setSize(((vec2f_t)new_resolution).to_sf());
    world_view.zoom(zoom);
    world_render.setTextureRect(sf::IntRect(vec2i_t(0, 0).to_sf(), ((vec2i_t)new_resolution).to_sf()));

    final_view.setSize(((vec2f_t)new_resolution).to_sf());
    final_view.setCenter(((vec2f_t)new_resolution * .5f).to_sf());
}

void fun::wndmgr::Window::DrawWorld(const sf::Drawable& drawable, fun::layer_t layer) {
    world_queue.Add(drawable, layer);
}

void fun::wndmgr::Window::DrawUI(const sf::Drawable& drawable, fun::layer_t layer) {
    ui_queue.Add(drawable, layer);
}

void fun::wndmgr::Window::Display(const sf::Color& bg_color, const sf::Shader* shader) {
    world_buffer.clear(bg_color);

    world_buffer.setView(world_view);
    world_buffer.draw(world_queue);
    world_buffer.display();

    world_render.setTexture(world_buffer.getTexture());

    render.setView(final_view);
    render.draw(world_render, shader);

#if defined(USES_IMGUI)
    ImGui::SFML::Render(render);
#endif

    render.display();

    world_queue.Clear();
}

void fun::wndmgr::Window::PollEvents() {
    sf::Event event;

    float curr_zoom_value;

    while (render.pollEvent(event)) {
#if defined(USES_IMGUI)
        ImGui::SFML::ProcessEvent(event);
#endif
        switch (event.type) {
            case sf::Event::Closed:
                render.close();

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

fun::vec2i_t fun::wndmgr::Window::GetMouseScreenPosition() {
    return sf::Mouse::getPosition(render);
}

fun::vec2f_t fun::wndmgr::Window::GetMouseWorldPosition() {
    return ScreenToWorld(GetMouseScreenPosition());
}

fun::vec2f_t fun::wndmgr::Window::ScreenToWorld(const fun::vec2i_t& p) {
    world_buffer.setView(world_view);

    return world_buffer.mapPixelToCoords(p.to_sf());
}

fun::vec2i_t fun::wndmgr::Window::WorldToScreen(const fun::vec2f_t& p) {
    world_buffer.setView(world_view);

    return world_buffer.mapCoordsToPixel(p.to_sf());
}
