#include "render/window/window.h"
#include "render/window/window_data.h"

fun::render::window_t::window_t(const window_data_t& data) :
    renderer(sf::VideoMode(data.size.x, data.size.y), data.name, data.style, data.settings),
    m_is_focused(true),
    m_zoom(1),
    ui_invalidated(false)
{
    refresh_window();

    world_view.setCenter(0, 0);
}

void fun::render::window_t::refresh_window() {
    const vec2u_t& new_resolution = renderer.getSize();

    world_buffer.create(new_resolution.x, new_resolution.y, renderer.getSettings());
    world_view.setSize(world_view_height * new_resolution.x / new_resolution.y, world_view_height);
    world_view.zoom(m_zoom);
    world_render.setTextureRect(sf::IntRect(vec2i_t(0, 0).to_sf(), ((vec2i_t)new_resolution).to_sf()));

    ui_buffer.create(new_resolution.x, new_resolution.y, renderer.getSettings());
    ui_view.setSize(((vec2f_t)new_resolution).to_sf());
    ui_view.setCenter(((vec2f_t)new_resolution * .5f).to_sf());
    ui_render.setTextureRect(sf::IntRect(vec2i_t(0, 0).to_sf(), ((vec2i_t)new_resolution).to_sf()));
}

bool fun::render::window_t::is_open() const {
    return renderer.isOpen();
}

bool fun::render::window_t::is_focused() const {
    return m_is_focused;
}

float fun::render::window_t::get_zoom() const {
    return m_zoom;
}

void fun::render::window_t::zoom(float zoom_value) {
    m_zoom *= zoom_value;

    world_view.zoom(zoom_value);
}

void fun::render::window_t::zoom_into(vec2f_t screen_pos, float zoom_value) {
    m_zoom *= zoom_value;

    auto screen_01 = screen_pos / (fun::vec2f_t)(fun::vec2u_t)renderer.getSize() - .5f;
    auto world = world_view.getSize();

    world_view.zoom(zoom_value);

    world_view.move((screen_01 * (fun::vec2f_t)(world - world_view.getSize())).to_sf());
}

sf::RenderWindow& fun::render::window_t::get_renderer() {
    return renderer;
}

fun::vec2u_t fun::render::window_t::get_resoluton() {
    return renderer.getSize();
}

void fun::render::window_t::target_framerate(uint32_t fps) {
    renderer.setFramerateLimit(fps);
}

void fun::render::window_t::set_vsync(bool value) {
    renderer.setVerticalSyncEnabled(value);
}

void fun::render::window_t::set_world_view(vec2f_t center, float height) {
    m_zoom *= 1.f;
    world_view.zoom(1.f);

    world_view_height = height;

    world_view.setCenter(center.to_sf());

    auto size = world_view.getSize();
    world_view.setSize(height * size.x / size.y, height);
}

void fun::render::window_t::move_world_view(vec2f_t offset) {
    world_view.move((offset * fun::vec2f_t { 1.f, -1.f }).to_sf());
}

void fun::render::window_t::draw_world(const sf::Drawable& drawable, layer_t layer, const sf::RenderStates& render_states) {
    world_queue.add(drawable, layer, render_states);
}

void fun::render::window_t::draw_ui(const sf::Drawable& drawable, layer_t layer, const sf::RenderStates& render_states) {
    ui_queue.add(drawable, layer, render_states);
}

void fun::render::window_t::invalidate_ui() {
    ui_invalidated = true;
}

void fun::render::window_t::display(const rgb_t& bg_color, const sf::Shader* shader) {
    world_buffer.clear(bg_color.to_sf());
    world_buffer.setView(world_view);
    world_buffer.draw(world_queue);
    world_buffer.display();
    world_render.setTexture(world_buffer.getTexture());

    if (ui_invalidated) {
        ui_buffer.clear(fun::rgba_t::transparent.to_sf());
        ui_buffer.setView(ui_view);
        ui_buffer.draw(ui_queue);
        ui_buffer.display();
        ui_render.setTexture(ui_buffer.getTexture());

        ui_invalidated = false;
    }

    renderer.setView(ui_view);
    renderer.draw(world_render, shader);
    renderer.draw(ui_render);

#if defined(FE2D_IMGUI)
    ImGui::SFML::Render(renderer);
#endif

    renderer.display();

    world_queue.clear();
    ui_queue.clear();
}

void fun::render::window_t::register_event_handler(sf::Event::EventType event_type, std::function<void(window_t&, const sf::Event&)> handler_function) {
    m_event_handlers[event_type] = handler_function;
}

void fun::render::window_t::update() {
    sf::Event event;

    float curr_zoom_value;

    while (renderer.pollEvent(event)) {
#if defined(FE2D_IMGUI)
        ImGui::SFML::ProcessEvent(event);
#endif
        switch (event.type) {
            case sf::Event::Closed:
                renderer.close();

                break;

            case sf::Event::GainedFocus:
                m_is_focused = true;

                break;

            case sf::Event::LostFocus:
                m_is_focused = false;

                break;

            case sf::Event::Resized:
                refresh_window();

                break;
        }

        
        if (m_event_handlers[event.type].has_value()) {
            m_event_handlers[event.type].value()(*this, event);
        }
    }
}

fun::vec2i_t fun::render::window_t::get_mouse_screen_position() {
    return sf::Mouse::getPosition(renderer);
}

fun::vec2f_t fun::render::window_t::get_mouse_world_position() {
    return screen_to_world(get_mouse_screen_position());
}

fun::vec2f_t fun::render::window_t::screen_to_world(const fun::vec2i_t p) {
    world_buffer.setView(world_view);

    return world_buffer.mapPixelToCoords(p.to_sf());
}

fun::vec2i_t fun::render::window_t::world_to_screen(const fun::vec2f_t p) {
    world_buffer.setView(world_view);

    return world_buffer.mapCoordsToPixel(p.to_sf());
}

void fun::render::window_t::set_cursor_visible(bool visible) {
    renderer.setMouseCursorVisible(visible);
}

void fun::render::window_t::set_cursor_grabbed(bool grabbed) {
    renderer.setMouseCursorGrabbed(grabbed);
}
