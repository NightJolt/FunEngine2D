#include "fun_engine_2d/core/include/globals.h"

#include "fun_engine_2d/core/include/tools/Command.h"
#include "fun_engine_2d/core/include/render/RenderQueue.h"
#include "fun_engine_2d/core/include/render/WindowManager.h"
#include "fun_engine_2d/core/include/R.h"
#include "fun_engine_2d/core/include/Input.h"
#include "fun_engine_2d/core/include/_Time.h"
#include "fun_engine_2d/experimental/include/interactable/Interaction.h"
#include "fun_engine_2d/experimental/include/object_system/Level.h"
#include "fun_engine_2d/experimental/include/drawable/RoundedRect.h"

#if defined(UNIX)
#include "fun_engine_2d/kernel/include/cudatest.cuh"
#endif

// USED FOR TESTING
int main () {
    glob_init();

    fun::R::LoadResources();

    fun::WindowManager::Init("FunEngine2D");

    fun::WindowManager::WindowData* window_data = fun::WindowManager::main_window;
    window_data->window.resetGLStates();
    window_data->window.setFramerateLimit(60);
    window_data->window.setVerticalSyncEnabled(false);

    ImGui::SFML::Init(window_data->window);

#if defined(UNIX)
    std::cout << fun::CudaTesting::AddTwoNumbers(420, 69) << std::endl;
#endif

    sf::CircleShape a(100, 30);
    sf::CircleShape b(100, 30);

    a.move(100, 0);

    a.setFillColor(sf::Color::Red);
    b.setFillColor(sf::Color::Green);

    while (window_data->window.isOpen()) {
        fun::Input::Listen();
        fun::Time::Recalculate();
        fun::Interaction::Update();
        ImGui::SFML::Update(window_data->window, fun::Time::DeltaTimeObject());

        window_data->PollEvents();
        window_data->world_view.move(fun::Input::K2D() * sf::Vector2f(1, -1) * 30.f);

        a.setPosition(window_data->ScreenToWorld(sf::Mouse::getPosition(window_data->window)) - a.getRadius());

        window_data->AddWorld(a, 420);
        window_data->AddWorld(b, 69);

        window_data->Display(sf::Color::Black);
    }

    ImGui::SFML::Shutdown();

    return 0;
};