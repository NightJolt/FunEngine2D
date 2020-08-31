/*#include "imgui.h"
#include "imgui_internal.h"
#include "imgui-SFML.h"*/

#include <iostream>

#include "Input.h"
#include "R.h"
#include "FTime.h"
#include "Collider.h"
#include "ParticleSystem.h"

#include "UI/UI.h"
#include "UI/UISprite.h"

#include "globals.h"

using namespace std;
using namespace sf;

int main() {
    ios::sync_with_stdio(false);

    RenderWindow window(VideoMode(INIT_SCREEN_SIZE.x, INIT_SCREEN_SIZE.y), "CPP2PChat");
    /*ImGui::SFML::Init(window);
    window.resetGLStates();*/

    R::LoadResources();

    View view(INIT_VIEW_ORIGIN, INIT_VIEW_SIZE);
    Vector2f screen_resolution = Vector2f(INIT_SCREEN_SIZE.x, INIT_SCREEN_SIZE.y);
    View ui_view(sf::FloatRect (0, 0, screen_resolution.x, screen_resolution.y));

    Text fps_display;
    fps_display.setFont(R::fonts[0]);
    fps_display.setCharacterSize(24);
    fps_display.setPosition(-700, -600);

    ParticleSystem particle_system(ParticleSystem::Sprite, ParticleSystem::Loop, 100, 0.1f);
    particle_system.PushTexture(&R::textures[0]);
    for (int i = 0; i < 13; i++) {
        particle_system.PushTextureRect(FloatRect(sf::Vector2f(0, 72 * i), sf::Vector2f(72, 72)));
    }

    UISprite uis(FloatRect(10, 10, 100, 100), &R::textures[1]);
    uis.settings.stick_to_point = UI::StickPoint::TOP_LEFT;

    while (window.isOpen()) {
        Input::Listen();
        FTime::Recalculate();

        Event event;
        while (window.pollEvent(event)) {
            //ImGui::SFML::ProcessEvent(event);

            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseWheelMoved:
                    view.zoom(event.mouseWheel.delta > 0 ? 0.9f : 1.1f);
                    break;
                case Event::Resized:
                    Vector2f ratio = (Vector2f)window.getSize() / screen_resolution;
                    screen_resolution = (Vector2f)window.getSize();
                    view.setSize(view.getSize() * ratio);
                    uis.Rescale(Math::Swap(ratio));
            }
        }

        view.move(Input::K2D() * .3f * view.getSize() * Vector2f(1, -1) * FTime::DeltaTime());
        view.move(Input::J2D() * .3f * view.getSize() * FTime::DeltaTime());

        fps_display.setString(to_string((int)FTime::FPS())/* + " " + to_string(particle_system.Count())*/);

        particle_system.Update();

        window.clear();

        // world space
        window.setView(view);
        window.draw(fps_display);
        particle_system.Draw(window);

        // screen space
        window.setView(ui_view);
        window.draw(uis);

        window.display();
    }

    //ImGui::SFML::Shutdown();

    return 0;
}