#include "tools/Debugger.h"



static bool unit_coord_enabled;
static bool debug_log_enabled;


void fun::debugger::display_debug_menu() {
    ImGui::Begin("Debug Menu");
    
        ImGui::Checkbox("unit coord display", &unit_coord_enabled);
        ImGui::Checkbox("debug log display", &debug_log_enabled);

    ImGui::End();
}



sf::Text unit_coord_text;

void fun::debugger::display_unit_coord(const sf::Vector2f& pos, float character_size, int layer, sf::Color color, const std::string& font_name) {
    if (!unit_coord_enabled) return;

    const float zoom = fun::wndmgr::main_window->zoom;

    unit_coord_text.setFont(fun::resources::get_font(font_name));
    unit_coord_text.setColor(color);
    unit_coord_text.setCharacterSize(character_size);
    unit_coord_text.setScale({ zoom, zoom });
    unit_coord_text.setPosition(pos + sf::Vector2f(0, 20.f * zoom));
    unit_coord_text.setString(sf::to_string(static_cast <sf::Vector2i> (pos)));

    fun::wndmgr::main_window->DrawWorld(unit_coord_text, layer);
}



static std::vector <std::string> channels = std::vector <std::string> ();
static std::vector <std::vector <std::string>> logs = std::vector <std::vector <std::string>> ();
static std::vector <std::pair <uint32_t, uint32_t>> order = std::vector <std::pair <uint32_t, uint32_t>> ();


void fun::debugger::push_msg(const std::string& msg, const std::string& channel) {
    int ind = -1;

    for (int i = 0 ; i < channels.size(); i++) {
        if (channels[i] == channel) {
            ind = i;

            break;
        }
    }

    if (ind == -1) {
        channels.emplace_back(channel);
        ind = channels.size() - 1;
    }

    if (logs.size() == ind) logs.push_back(std::vector <std::string> ());

    logs[ind].emplace_back(msg);
    order.emplace_back(ind, logs[ind].size() - 1);
}

void fun::debugger::push_cmd(const fun::Command& cmd, const std::string& channel) {}

void fun::debugger::display_debug_log() {
    if (!debug_log_enabled) return;

    ImGui::Begin("Debugger");
        ImGui::BeginTabBar("Channels");

        if (ImGui::BeginTabItem("all##tab")) {
                ImGui::BeginChild("all##child");

                for (auto& msg : order) {
                    ImGui::Text(("[" + channels[msg.first] + "] " + logs[msg.first][msg.second]).c_str());
                }

                ImGui::EndChild();
            ImGui::EndTabItem();
        }

        for (int i = 0 ; i < channels.size(); i++) {
            if (ImGui::BeginTabItem(channels[i].c_str())) {
                    ImGui::BeginChild(("##" + channels[i]).c_str());

                    for (auto& msg : logs[i]) {
                        ImGui::Text(msg.c_str());
                    }
                    
                    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                        ImGui::SetScrollHereY(1.0f);

                    ImGui::EndChild();
                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
    ImGui::End();
}



// void fun::debugger::display_unit_lines(uint32_t layer, sf::Color color, const std::string& font_name) {
    // const auto& font = fun::resources::get_font(font_name);
    // const float step = 10.f;
    // const float fade = 100.f;

    // auto* window = fun::wndmgr::main_window;

    // sf::Vector2f top_left = fun::wndmgr::main_window->ScreenToWorld({ 0, 0 });
    // sf::Vector2f bottom_right = fun::wndmgr::main_window->ScreenToWorld((sf::Vector2i)window->render.getSize());
// }