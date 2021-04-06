/*#include "imgui.h"
#include "imgui_internal.h"
#include "imgui-SFML.h"*/

#include <iostream>

#include "Input.h"
#include "R.h"
#include "Time.h"

/*#include "Collider.h"
#include "ParticleSystem.h"

#include "UI/UI.h"
#include "UI/UISprite.h"
#include "UI/UIButton.h"*/

#include "globals.h"

using namespace std;
using namespace sf;

int main() {
    ios::sync_with_stdio(false);

    RenderWindow window(VideoMode(INIT_SCREEN_SIZE.x, INIT_SCREEN_SIZE.y), "FunEngine");
    Event event;

    R::LoadResources();

    View view(INIT_VIEW_ORIGIN, INIT_VIEW_SIZE);
    Vector2f screen_resolution = Vector2f(INIT_SCREEN_SIZE.x, INIT_SCREEN_SIZE.y);

    Text fps_display;
    fps_display.setFont(R::fonts[0]);
    fps_display.setCharacterSize(24);
    fps_display.setPosition(-700, -600);

    /*ParticleSystem particle_system(ParticleSystem::RenderType::Sprite, ParticleSystem::Loop, 100000, 0);
    particle_system.PushTexture(&R::textures[0]);
    for (int j = 0; j < 13; j++) {
        for (int i = 0; i < 13; i++) {
            particle_system.PushTextureRect(FloatRect(sf::Vector2f(72 * j, 72 * i), sf::Vector2f(72, 72)));
        }
    }*/
    //particle_system.settings.gravity = Vector2f(0, 40);

    /*UIButton uis(FloatRect(10, 10, 100, 100));
    uis.SetCallback([](){
        cout << "clicked" << endl;
    });
    uis.settings.stick_to_point = UI::StickPoint::TOP_LEFT;
    uis.text.setFont(R::fonts[0]);
    uis.text.setString("Hello");
    uis.SetTexure(&R::textures[1]);
    uis.settings.colors[UI::State::HOVERED] = Color(200, 200, 200, 255);
    uis.settings.colors[UI::State::PRESSED] = Color(100, 100, 100, 255);

    UIText uit(Vector2f(200, 100));
    uit.text.setFont(R::fonts[0]);
    uit.text.setString("Hello");
    uit.settings.stick_to_point = UI::StickPoint::CENTER;*/

    while (window.isOpen()) {
        Input::Listen();
        FTime::Recalculate();
        while (window.pollEvent(event)) {
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

                    Vector2f scale_val = Math::Sqrt(ratio * Math::Swap(ratio));
                    /*uis.Rescale(scale_val);
                    uit.Rescale(scale_val);*/

                    break;
            }
        }

        //uis.Update(window);

        view.move(Input::K2D() * .3f * view.getSize() * Vector2f(1, -1) * FTime::DeltaTime());
        view.move(Input::J2D() * .3f * view.getSize() * FTime::DeltaTime());

        fps_display.setString(to_string((int)FTime::FPS()));

        //particle_system.Update();

        window.clear();

        // world space
        window.setView(view);
        window.draw(fps_display);
        //particle_system.Draw(window);

        // screen space
        window.setView(View(sf::FloatRect (0, 0, screen_resolution.x, screen_resolution.y)));
        //window.draw(uis);
        //window.draw(uit);

        window.display();
    }

    //ImGui::SFML::Shutdown();

    return 0;
}