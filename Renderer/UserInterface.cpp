#include "UserInterface.h"

UserInterface::UserInterface() = default;

void UserInterface::drawInfo(float dt, int vertices) {
    static char fps_text[20];
    static char vertex_count_text[50];
    static const ImVec2 windowSize(150, 40);

    float framerate = 1.0f / dt;
    snprintf(fps_text, sizeof(fps_text), "FPS: %.1f", framerate);
    snprintf(vertex_count_text, sizeof(vertex_count_text), "Vertices:%.1d", vertices);

    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::Begin("Framerate", nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing);
    ImGui::TextUnformatted(fps_text);
    ImGui::TextUnformatted(vertex_count_text);
    ImGui::End();
}
