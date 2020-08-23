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

    View view(Vector2f(0, 0), Vector2f(1920, 1440));

    RectangleShape r1;
    r1.setPosition(Vector2f(-125, -150));
    r1.setSize(Vector2f(250, 300));
    r1.setFillColor(Color::Transparent);
    r1.setOutlineColor(Color::Blue);
    r1.setOutlineThickness(2);
    Collider::Rect c1(Vector2f(0, 0), Vector2f(250, 300));

    Vertex line[] = {
            Vertex(Vector2f(-960.f, -720.f)),
            Vertex(Vector2f(0, 0))
    };

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

        line[0].position += Input::K2D(
                Keyboard::Key::J,
                Keyboard::Key::L,
                Keyboard::Key::K,
                Keyboard::Key::I
            ) * .3f * view.getSize() * Vector2f(1, -1) * FTime::DeltaTime();
        line[1].position = Math::ScreenToWorld(sf::Mouse::getPosition(window), window);

        if (Collider::RayVsRect(Collider::Ray(line[0].position, line[1].position - line[0].position), c1)) {
             line[0].color = Color::Green;
             line[1].color = Color::Green;
        } else {
            line[0].color = Color::Red;
            line[1].color = Color::Red;
        }

        Vertex aim_line[] = {
                line[0],
                line[1]
        };

        aim_line[0].color = aim_line[1].color = Color(255, 150, 0, 200);
        aim_line[1].position = aim_line[0].position + Math::Direction(aim_line[0].position, aim_line[1].position) * 5000.f;

        window.setView(view);
        window.clear();

        window.draw(r1);
        window.draw(aim_line, 2, Lines);
        window.draw(line, 2, Lines);

        window.display();
    }

    //ImGui::SFML::Shutdown();

    return 0;
}