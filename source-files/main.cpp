#include "imgui.h"
#include "imgui_internal.h"
#include "imgui-SFML.h"

#include "globals.h"

#include "Input.h"
#include "R.h"
#include "FTime.h"
#include "Collider.h"

#include <iostream>

using namespace std;
using namespace sf;

int main() {
    ios::sync_with_stdio(false);

    RenderWindow window(VideoMode(1920, 1440), "CPP2PChat");
    /*ImGui::SFML::Init(window);
    window.resetGLStates();*/

    R::LoadResources();

    Text key_a, key_b, key_c;
    key_a.setFont(R::fonts[0]);
    key_a.setCharacterSize(72);
    key_a.setPosition(10, 10);
    key_b.setFont(R::fonts[0]);
    key_b.setCharacterSize(72);
    key_b.setPosition(10, -40);
    key_c.setFont(R::fonts[0]);
    key_c.setCharacterSize(72);
    key_c.setPosition(10, -90);

    Sprite sp;
    sp.setScale(2, 2);
    sp.setTexture(R::textures[0]);
    sp.setPosition(100, 100);

    View view(Vector2f(0, 0), Vector2f(1920, 1440));

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

        view.move(Input::K2D(
                Keyboard::Key::A,
                Keyboard::Key::D,
                Keyboard::Key::S,
                Keyboard::Key::W
        ) * .3f * view.getSize() * Vector2f(1, -1) * FTime::DeltaTime());

        if (Input::Pressed(Keyboard::Space)) {
            View v = window.getView();
            v.zoom(2);
            window.setView(v);
        }

        key_a.setString(to_string(Mouse::getPosition(window)));
        key_b.setString(to_string(Math::ScreenToWorld(Mouse::getPosition(window), window)));
        key_c.setString(to_string(Math::WorldToScreen(Math::ScreenToWorld(Mouse::getPosition(window), window), window)));

        window.setView(view);
        window.clear();

        //ImGui::SFML::Render(window);
        window.draw(key_a);
        window.draw(key_b);
        window.draw(key_c);
        window.draw(sp);

        window.display();
    }

    //ImGui::SFML::Shutdown();

    return 0;
}