#include "globals.h"

#include "Tools/Command.h"
#include "Render/RenderQueue.h"
#include "Render/WindowManager.h"
#include "R.h"
#include "Input.h"
#include "Time.h"

#include "../kernel/header_files/cudatest.cuh"

using namespace std;
using namespace sf;
using namespace fun;

// USED FOR TESTING
int main () {

    cout << CudaTesting::AddTwoNumbers(420, 69) << endl;

    sf::CircleShape a(100, 30);
    sf::CircleShape b(100, 30);

    a.move(100, 0);

    a.setFillColor(sf::Color::Red);
    b.setFillColor(sf::Color::Green);

    glob_init();

    WindowManager::Init("FunEngine2D");

    R::LoadResources();

    while (WindowManager::main_window->window.isOpen()) {
        Input::Listen();
        fun::Time::Recalculate();

        WindowManager::main_window->PollEvents();

        WindowManager::main_window->AddWorld(a, 2);
        WindowManager::main_window->AddWorld(b, 2);

        WindowManager::main_window->Clear(sf::Color::Black);
        WindowManager::main_window->Draw();
        WindowManager::main_window->Display();
    }

    return 0;
};