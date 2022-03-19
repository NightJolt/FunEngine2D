#include "render/window_manager.h"

fun::winmgr::window_t* fun::winmgr::main_window = nullptr;

fun::winmgr::window_data_t::window_data_t(const std::string& name, const vec2u_t size, fun::mask32_t style, const sf::ContextSettings& settings) :
    name(name),
    size(size),
    style(style),
    settings(settings)
{   
}

void fun::winmgr::init(const window_data_t& data) {
    main_window = new window_t(data);

    main_window->render.setFramerateLimit(60);
    main_window->render.setVerticalSyncEnabled(false);

#if defined(USES_IMGUI)
    main_window->render.resetGLStates();

    ImGui::SFML::Init(main_window->render);
#endif
}

void fun::winmgr::update() {
    main_window->poll_events();

#if defined(USES_IMGUI)
    ImGui::SFML::Update(main_window->render, fun::time::delta_time_object());
#endif
}

void fun::winmgr::close() {
#if defined(USES_IMGUI)
    ImGui::SFML::Shutdown();
#endif

    delete main_window;
}

fun::winmgr::window_t::window_t(const window_data_t& data) :
    render(sf::VideoMode(data.size.x, data.size.y), data.name, data.style, data.settings),
    is_focused(false),
    zoom(1)
{
    refresh_window();

    world_view.setCenter(0, 0);
}

void fun::winmgr::window_t::refresh_window() {
    const vec2u_t& new_resolution = render.getSize();

    world_buffer.create(new_resolution.x, new_resolution.y, render.getSettings());
    world_view.setSize(((vec2f_t)new_resolution).to_sf());
    world_view.zoom(zoom);
    world_render.setTextureRect(sf::IntRect(vec2i_t(0, 0).to_sf(), ((vec2i_t)new_resolution).to_sf()));

    final_view.setSize(((vec2f_t)new_resolution).to_sf());
    final_view.setCenter(((vec2f_t)new_resolution * .5f).to_sf());
}

void fun::winmgr::window_t::draw_world(const sf::Drawable& drawable, fun::layer_t layer) {
    world_queue.add(drawable, layer);
}

void fun::winmgr::window_t::draw_ui(const sf::Drawable& drawable, fun::layer_t layer) {
    ui_queue.add(drawable, layer);
}

void fun::winmgr::window_t::display(const sf::Color& bg_color, const sf::Shader* shader) {
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

    world_queue.clear();
}

void fun::winmgr::window_t::poll_events() {
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
                refresh_window();

                // ? FOR UI
                // sf::Vector2f scale_val = Math::Sqrt(ratio * Math::Swap(ratio));
                // fps.Rescale(scale_val);

                break;
        }
    }
}

fun::vec2i_t fun::winmgr::window_t::get_mouse_screen_position() {
    return sf::Mouse::getPosition(render);
}

fun::vec2f_t fun::winmgr::window_t::get_mouse_world_position() {
    return screen_to_world(get_mouse_screen_position());
}

fun::vec2f_t fun::winmgr::window_t::screen_to_world(const fun::vec2i_t& p) {
    world_buffer.setView(world_view);

    return world_buffer.mapPixelToCoords(p.to_sf());
}

fun::vec2i_t fun::winmgr::window_t::world_to_screen(const fun::vec2f_t& p) {
    world_buffer.setView(world_view);

    return world_buffer.mapCoordsToPixel(p.to_sf());
}
