//
// Created by Flo on 20/04/2023.
//

#include "TerrainScene.hpp"

#include <Renderable/Terrain/Terrain.hpp>
#include <Renderable/SkyBox.hpp>

#include "../UISystem/UiWindow.hpp"
#include "../GameLoop/GameLoop.hpp"
#include "../UISystem/UiButton.hpp"
#include "../UISystem/UiInputInt.hpp"
#include "../UISystem/UISliderFloat.hpp"
#include "../UISystem/UiSliderInt.hpp"

void TerrainScene::Init()
{
    AddObject<SkyBox>(new SkyBox());

    {
        m_terrain = new Terrain();
        m_terrainGenerator = new TerrainGenerator(m_terrain);
        AddObject<TerrainGenerator>(m_terrainGenerator);
        AddObject<Terrain>(m_terrain);

        m_terrainGenerator->SetSeed(121);
        m_terrainGenerator->GenerateAllChunks(0, 0);
    }

    {
        auto infoWindow = new UIWindow(
                "Infos",
                ImVec2(150, 45),
                ImGuiCond_Always,
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoFocusOnAppearing
        );

        m_fpsText = new UIText("FPS: 0");
        infoWindow->AddChild(m_fpsText);
        m_verticesCountText = new UIText("Vertices: 0");
        infoWindow->AddChild(m_verticesCountText);

        AddObject(infoWindow);
    }

    {
        auto window = new UIWindow("Camera");

        m_cameraPosText = new UIText("Camera pos: 0, 0, 0");
        window->AddChild(m_cameraPosText);

        m_cameraChunkText = new UIText("Camera Chunk: 0, 0");
        window->AddChild(m_cameraChunkText);

        AddObject(window);
    }

    {
        auto window = new UIWindow("Terrain");

        auto changeVerticesModeButton = new UIButton("Change vertices mode");
        changeVerticesModeButton->SetOnClick([this]()
        {
            m_verticesMode++;
            if(m_verticesMode > 2)
                m_verticesMode = 0;
            SetVerticesMode(m_verticesMode);
        });
        window->AddChild(changeVerticesModeButton);

        auto seedInput = new UIInputInt("Seed", m_terrainGenerator->GetSeed(), 0, 255);
        seedInput->SetOnValueChange([this](int value)
        {
            m_terrainGenerator->SetSeed(value);
        });
        window->AddChild(seedInput);

        // Slider Frequency
        auto frequencySlider = new UISliderFloat("Frequency", m_terrainGenerator->m_frequency, 0.0f, 10.0f);
        frequencySlider->SetOnValueChange([this](float value)
        {
            m_terrainGenerator->m_frequency = value;
        });
        window->AddChild(frequencySlider);

        // Slider Redistribution
        auto redistributionSlider = new UISliderFloat("Redistribution", m_terrainGenerator->m_redistribution, 0.0f, 10.0f);
        redistributionSlider->SetOnValueChange([this](float value)
        {
            m_terrainGenerator->m_redistribution = value;
        });
        window->AddChild(redistributionSlider);

        // Slider Amplitude
        auto amplitudeSlider = new UISliderFloat("Amplitude", m_terrainGenerator->m_amplitude, 0.0f, 10.0f);
        amplitudeSlider->SetOnValueChange([this](float value)
        {
            m_terrainGenerator->m_amplitude = value;
        });
        window->AddChild(amplitudeSlider);

        // Slider Octaves
        auto octavesSlider = new UISliderFloat("Octaves", m_terrainGenerator->m_octaves, 0.0f, 10.0f);
        octavesSlider->SetOnValueChange([this](float value)
        {
            m_terrainGenerator->m_octaves = value;
        });
        window->AddChild(octavesSlider);

        // Slider Lacunarity
        auto lacunaritySlider = new UISliderFloat("Lacunarity", m_terrainGenerator->m_lacunarity, 0.0f, 10.0f);
        lacunaritySlider->SetOnValueChange([this](float value)
        {
            m_terrainGenerator->m_lacunarity = value;
        });
        window->AddChild(lacunaritySlider);

        // Slider m_chunksAroundUs
        auto chunksAroundUsSlider = new UISliderInt("Chunks around us", m_terrainGenerator->m_chunksAroundUs, 0, 16);
        chunksAroundUsSlider->SetOnValueChange([this](int value)
        {
            m_terrainGenerator->m_chunksAroundUs = value;
        });
        window->AddChild(chunksAroundUsSlider);

        auto button = new UIButton("Generate");
        button->SetOnClick([this]()
        {
            auto camPos = GameLoop::Instance()->camera->GetTransform().pos;
            m_terrainGenerator->SetNeedToGenerateAllChunks();
            m_verticesCount = m_terrain->GetTotalVertices();
        });
        window->AddChild(button);

        AddObject(window);
    }

    m_verticesCount = m_terrain->GetTotalVertices();
}

void TerrainScene::OnUpdate(float deltaTime)
{
    auto camPos = GameLoop::Instance()->camera->GetTransform().pos;

    if(m_terrainGenerator->IsNeedToGenerateAllChunks())
        m_terrainGenerator->GenerateAllChunks(camPos.x, camPos.z);

    m_fpsText->SetText("FPS: " + std::to_string(static_cast<int>(1 / deltaTime)));
    m_verticesCountText->SetText("Vertices: " + std::to_string(m_verticesCount));

    m_cameraPosText->SetText("Camera pos: " + std::to_string(camPos.x) + ", " + std::to_string(camPos.y) + ", " + std::to_string(camPos.z));

    auto chunkPos = ChunkContainer::GetChunkIndex(camPos.x, camPos.z);
    m_cameraChunkText->SetText("Camera Chunk: " + std::to_string(chunkPos.first) + ", " + std::to_string(chunkPos.second));
}

void TerrainScene::SetVerticesMode(uint32_t mode)
{
    switch (mode) {
        case 0:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case 1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
        case 2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        default:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
    }
}
