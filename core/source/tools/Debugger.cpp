#include "tools/Debugger.h"

std::unordered_map <std::string, std::string> channels = std::unordered_map <std::string, std::string> ();
std::unordered_map <std::string, std::vector <std::string>> logs = std::unordered_map <std::string, std::vector <std::string>> ();
std::vector <std::pair <std::string*, std::string*>> order = std::vector <std::pair <std::string*, std::string*>> ();


void fun::debugger::push_msg(const std::string& msg, const std::string& channel) {
    order.emplace_back(&(channels[channel] = std::string(channel)), &logs[channel].emplace_back(msg));
}

void fun::debugger::push_cmd(const fun::Command& cmd, const std::string& channel) {}

void fun::debugger::display() {
    ImGui::Begin("Debugger");
        ImGui::BeginTabBar("Channels");

        if (ImGui::BeginTabItem("all##tab")) {
                ImGui::BeginChild("all##child");

                for (auto& msg : order) {
                    ImGui::Text(("[" + *msg.first + "] " + *msg.second).c_str());
                }

                ImGui::EndChild();
            ImGui::EndTabItem();
        }

        for (auto [channel, msgs] : logs) {
            if (ImGui::BeginTabItem(channel.c_str())) {
                    ImGui::BeginChild(("##" + channel).c_str());

                    for (auto& msg : msgs) {
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