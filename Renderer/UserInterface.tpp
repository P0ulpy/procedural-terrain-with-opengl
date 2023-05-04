
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

void UserInterface::drawTerrainParameters(int seed, MapGenerator mapGenerator, const Point3f &cameraPos) {
    ImGui::Begin("Terrain parameters");
    if (ImGui::InputInt("Seed", &seed, 0, 256)) {
        //mapGenerator.setSeed(seed);
        mapGenerator.GenerateAllChunks(static_cast<int>(cameraPos.x), static_cast<int>(cameraPos.z));
    }

    if (ImGui::SliderFloat("Frequency", &mapGenerator.m_frequency, 0.0f, 10.0f, "%.2f")) {
        mapGenerator.GenerateAllChunks(static_cast<int>(cameraPos.x), static_cast<int>(cameraPos.z));
    }
    if (ImGui::SliderFloat("Redistribution", &mapGenerator.m_redistribution, 0.0f, 10.0f, "%.2f")) {
        mapGenerator.GenerateAllChunks(static_cast<int>(cameraPos.x), static_cast<int>(cameraPos.z));
    };
    if (ImGui::SliderInt("Nbr of Terraces", &mapGenerator.terraces, 0.0f, 100.0f, "%.2d")) {
        mapGenerator.GenerateAllChunks(static_cast<int>(cameraPos.x), static_cast<int>(cameraPos.z));
    }

    if (ImGui::Button("Change vertices mode")) {
        //
    }

    ImGui::End();
}
