#include "imgui.h"
#include "imgui_internal.h"
#include "imgui-SFML.h"

#include "Input.h"

using namespace std;
using namespace sf;

int main() {
    ios::sync_with_stdio(false);

    RenderWindow window(VideoMode(1920, 1440), "CPP2PChat");
    /*ImGui::SFML::Init(window);
    window.resetGLStates();*/

    Font andy_bold;
    andy_bold.loadFromFile("../R/fonts/andy_bold.ttf");
    Text key_a;
    key_a.setFont(andy_bold);
    key_a.setCharacterSize(72);
    key_a.setPosition(10, 10);

    while (window.isOpen()) {
        Input::Listen();

        Event event;
        while (window.pollEvent(event)) {
            //ImGui::SFML::ProcessEvent(event);

            if (event.type == Event::Closed) {
                window.close();
            }
        }

        key_a.setString(string("X: ") + to_string(Input::Hold(Keyboard::BackSlash)));

        window.clear();

        //ImGui::SFML::Render(window);
        window.draw(key_a);

        window.display();
    }

    //ImGui::SFML::Shutdown();

    return 0;
}