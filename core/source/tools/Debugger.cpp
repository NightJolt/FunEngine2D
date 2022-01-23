#include "tools/Debugger.h"

std::vector <std::string> channels = std::vector <std::string> ();
std::vector <std::vector <std::string>> logs = std::vector <std::vector <std::string>> ();
std::vector <std::pair <uint32_t, uint32_t>> order = std::vector <std::pair <uint32_t, uint32_t>> ();


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

void fun::debugger::display() {
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