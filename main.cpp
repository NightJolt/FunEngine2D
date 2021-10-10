#include "fun_engine_2d/core/include/globals.h"

#include "fun_engine_2d/core/include/tools/Command.h"
#include "fun_engine_2d/core/include/render/RenderQueue.h"
#include "fun_engine_2d/core/include/render/WindowManager.h"
#include "fun_engine_2d/core/include/R.h"
#include "fun_engine_2d/core/include/Input.h"
#include "fun_engine_2d/core/include/Time.h"

#include "fun_engine_2d/kernel/include/cudatest.cuh"

// USED FOR TESTING
int main () {
    std::cout << fun::CudaTesting::AddTwoNumbers(420, 69) << std::endl;

    sf::CircleShape a(100, 30);
    sf::CircleShape b(100, 30);

    a.move(100, 0);

    a.setFillColor(sf::Color::Red);
    b.setFillColor(sf::Color::Green);

    glob_init();

    fun::WindowManager::Init("FunEngine2D");

    fun::WindowManager::WindowData* window_data = fun::WindowManager::main_window;

    while (window_data->window.isOpen()) {
        fun::Input::Listen();
        fun::Time::Recalculate();

        window_data->PollEvents();

        a.setPosition(window_data->ScreenToWorld(sf::Mouse::getPosition(window_data->window)) - a.getRadius());

        window_data->AddWorld(a, 420);
        window_data->AddWorld(b, 69);

        window_data->Display(sf::Color::Black);
    }

    return 0;
};