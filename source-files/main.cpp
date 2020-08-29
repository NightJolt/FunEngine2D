#include "imgui.h"
#include "imgui_internal.h"
#include "imgui-SFML.h"

#include "globals.h"

#include "Input.h"
#include "R.h"
#include "FTime.h"
#include "Collider.h"
#include "ParticleSystem.h"

#include <iostream>

using namespace std;
using namespace sf;

int main() {
    ios::sync_with_stdio(false);

    RenderWindow window(VideoMode(INIT_SCREEN_SIZE), "CPP2PChat");
    /*ImGui::SFML::Init(window);
    window.resetGLStates();*/

    R::LoadResources();

    View view(INIT_VIEW_ORIGIN, INIT_VIEW_SIZE);

    Text fps_display;
    fps_display.setFont(R::fonts[0]);
    fps_display.setCharacterSize(24);
    fps_display.setPosition(-700, -600);

    ParticleSystem particle_system(ParticleSystem::Sprite, ParticleSystem::Loop, 10, 0.5f);
    particle_system.PushTexture(&R::textures[0]);
    particle_system.PushTextureRect(FloatRect(sf::Vector2f(0, 0), sf::Vector2f(900, 900)));
    particle_system.settings.emission_radius = 100.f;

    while (window.isOpen()) {
        Input::Listen();
        FTime::Recalculate();

        Event event;
        while (window.pollEvent(event)) {
            //ImGui::SFML::ProcessEvent(event);

            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::MouseWheelMoved) {
                view.zoom(event.mouseWheel.delta > 0 ? 0.9f : 1.1f);
            }
        }

        view.move(Input::K2D() * .3f * view.getSize() * Vector2f(1, -1) * FTime::DeltaTime());
        view.move(Input::J2D() * .3f * view.getSize() * FTime::DeltaTime());

        fps_display.setString(to_string((int)FTime::FPS())/* + " " + to_string(particle_system.Count())*/);

        particle_system.Update();

        window.setView(view);
        window.clear();

        window.draw(fps_display);
        particle_system.Draw(window);

        window.display();
    }

    //ImGui::SFML::Shutdown();

    return 0;
}