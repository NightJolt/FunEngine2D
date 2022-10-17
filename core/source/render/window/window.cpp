#include "render/window/window.h"
#include "render/window/window_data.h"

fun::render::window_t::window_t(const window_data_t& data) :
    renderer(sf::VideoMode(data.size.x, data.size.y), data.name, data.style, data.settings),
    m_is_focused(true),
    m_zoom(1)
{
    refresh_window();

    world_view.setCenter(0, 0);
}

void fun::render::window_t::refresh_window() {
    const vec2u_t& new_resolution = renderer.getSize();

    world_buffer.create(new_resolution.x, new_resolution.y, renderer.getSettings());
    world_view.setSize(view_height * renderer.getSize().x / renderer.getSize().y, view_height);
    world_view.zoom(m_zoom);
    world_render.setTextureRect(sf::IntRect(vec2i_t(0, 0).to_sf(), ((vec2i_t)new_resolution).to_sf()));

    final_view.setSize(((vec2f_t)new_resolution).to_sf());
    final_view.setCenter(((vec2f_t)new_resolution * .5f).to_sf());
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

sf::RenderWindow& fun::render::window_t::get_renderer() {
    return renderer;
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

    view_height = height;

    world_view.setCenter(center.to_sf());

    auto size = world_view.getSize();
    world_view.setSize(height * size.x / size.y, height);
}

void fun::render::window_t::draw_world(const sf::Drawable& drawable, layer_t layer, const sf::RenderStates& render_states) {
    world_queue.add(drawable, layer, render_states);
}

void fun::render::window_t::draw_ui(const sf::Drawable& drawable, layer_t layer, const sf::RenderStates& render_states) {
    ui_queue.add(drawable, layer, render_states);
}

void fun::render::window_t::display(const sf::Color& bg_color, const sf::Shader* shader) {
    world_buffer.clear(bg_color);

    world_buffer.setView(world_view);
    world_buffer.draw(world_queue);
    world_buffer.display();

    world_render.setTexture(world_buffer.getTexture());

    renderer.setView(final_view);
    renderer.draw(world_render, shader);

#if defined(USES_IMGUI)
    ImGui::SFML::Render(renderer);
#endif

    renderer.display();

    world_queue.clear();
}

void fun::render::window_t::poll_events() {
    sf::Event event;

    float curr_zoom_value;

    while (renderer.pollEvent(event)) {
#if defined(USES_IMGUI)
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

            case sf::Event::MouseWheelMoved: {
                curr_zoom_value = event.mouseWheel.delta > 0 ? .9f : 1.1f;
                m_zoom *= curr_zoom_value;

                auto mouse_pos = (fun::vec2f_t)get_mouse_screen_position() / (fun::vec2f_t)(fun::vec2u_t)renderer.getSize() - .5f;
                auto world = world_view.getSize();

                world_view.zoom(curr_zoom_value);

                world_view.move((mouse_pos * (fun::vec2f_t)(world - world_view.getSize())).to_sf());

                break;
            }

            case sf::Event::Resized:
                refresh_window();

                // ? FOR UI
                // sf::Vector2f scale_val = Math::Sqrt(ratio * Math::Swap(ratio));
                // fps.Rescale(scale_val);

                break;
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
