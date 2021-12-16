#include "render/WindowManager.h"

const sf::Vector2u fun::wndmgr::INIT_SCREEN_SIZE = sf::Vector2u(856, 482) * (unsigned)2;
const sf::Vector2f fun::wndmgr::INIT_VIEW_SIZE = sf::Vector2f(856, 482) * 2.f;
const sf::Vector2f fun::wndmgr::INIT_VIEW_ORIGIN = sf::Vector2f(0, 0);

fun::wndmgr::WindowData* fun::wndmgr::main_window = nullptr;

void fun::wndmgr::init(const std::string& window_name, i32 style, const sf::ContextSettings& settings) {
    main_window = new WindowData(window_name, style, settings);
}

fun::wndmgr::WindowData::WindowData(const std::string& window_name, i32 style, const sf::ContextSettings& settings) :
        window(sf::VideoMode(INIT_SCREEN_SIZE.x, INIT_SCREEN_SIZE.y), window_name, style, settings),
        world_view(INIT_VIEW_ORIGIN, INIT_VIEW_SIZE),
        ui_view(INIT_VIEW_ORIGIN, INIT_VIEW_SIZE),
        is_focused(false),
        zoom(1),
        resolution(INIT_SCREEN_SIZE)
{}

void fun::wndmgr::WindowData::AddWorld(const sf::Drawable& drawable, int order) {
    world_queue.Add(drawable, order);
}

void fun::wndmgr::WindowData::AddUI(const sf::Drawable& drawable, int order) {
    ui_queue.Add(drawable, order);
}

void fun::wndmgr::WindowData::Display(const sf::Color& bg_color) {
//    world_buffer.clear(bg_color);
    //ui_buffer.clear(sf::Color::Transparent);

    /*world_buffer.setView(world_view);
    window.setView(world_view);*/
//    world_buffer.draw(world_queue);
//    world_render.setTexture(world_buffer.getTexture());
//    window.draw(world_render);

    /*world_buffer.setView(world_view);
    world_buffer.draw(world_queue);
    world_render.setTexture(world_buffer.getTexture());

    ui_buffer.setView(ui_view);
    ui_buffer.draw(ui_queue);
    ui_render.setTexture(ui_buffer.getTexture());

    final_buffer.draw(world_render); // Apply World Shader
    final_buffer.draw(ui_render); // Apply UI Shader

    final_render.setTexture(final_buffer.getTexture());
    window.draw(final_render); // Apply Final Shader*/

//    world_queue.Clear();
//    ui_queue.Clear();

    world_buffer.clear(bg_color);

    world_buffer.setView(world_view);
    world_buffer.draw(world_queue);
    world_buffer.display();

    world_render.setTexture(world_buffer.getTexture());

    window.setView(final_view);
    window.draw(world_render/*, fun::R::shaders[0]*/);

#if defined(USES_IMGUI)
    ImGui::SFML::Render(window);
#endif

    window.display();

    world_queue.Clear();

//    window.clear(bg_color);
//
//    window.setView(world_view);
//    window.draw(world_queue);
//
//    window.display();
//
//    world_queue.Clear();
}

void fun::wndmgr::WindowData::PollEvents() {
    sf::Event event;

    float curr_zoom_value;

    while (window.pollEvent(event)) {
#if defined(USES_IMGUI)
        ImGui::SFML::ProcessEvent(event);
#endif
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
                curr_zoom_value = event.mouseWheel.delta > 0 ? .9f : 1.1f;

                zoom *= curr_zoom_value;

                world_view.zoom(curr_zoom_value);

                break;
            case sf::Event::Resized:

                const sf::Vector2u& new_resolution = window.getSize();
                const sf::Vector2f ratio = (sf::Vector2f)new_resolution / (sf::Vector2f)resolution;

                resolution = new_resolution;

                world_buffer.create(new_resolution.x, new_resolution.y, window.getSettings());
                world_view.setSize((sf::Vector2f)new_resolution * ratio);
                world_view.zoom(zoom);
                world_render.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(world_buffer.getTexture().getSize())));

                final_view.setSize((sf::Vector2f)new_resolution);
                final_view.setCenter((sf::Vector2f)new_resolution * .5f);

                //sf::Vector2f scale_val = Math::Sqrt(ratio * Math::Swap(ratio));
                //fps.Rescale(scale_val);

                break;
        }
    }
}

sf::Vector2i fun::wndmgr::WindowData::GetMouseScreenPosition() {
    return sf::Mouse::getPosition(window);
}

sf::Vector2f fun::wndmgr::WindowData::GetMouseWorldPosition() {
    return ScreenToWorld(GetMouseScreenPosition());
}

sf::Vector2f fun::wndmgr::WindowData::ScreenToWorld(const sf::Vector2i& p) {
    world_buffer.setView(world_view);

    return world_buffer.mapPixelToCoords(p);
}

sf::Vector2i fun::wndmgr::WindowData::WorldToScreen(const sf::Vector2f& p) {
    world_buffer.setView(world_view);

    return world_buffer.mapCoordsToPixel(p);
}
