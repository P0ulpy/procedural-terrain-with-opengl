#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <array>
#include "Math/Matrix.hpp"
#include "Map/MapGenerator.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "UserInterface.h"

int main()
{
    // set version of opengl to 4.6
    const sf::ContextSettings context_settings(24, 8, 4, 4, 6);
    // cr�e la fen�tre
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "OpenGL", sf::Style::Default, context_settings);
    window.setVerticalSyncEnabled(true);

    // activation de la fen�tre
    window.setActive(true);

    //ImGui::SFML::Init(window);

    // fucking lines of hell
    glewExperimental = GL_TRUE;
    if (glewInit())
        throw std::runtime_error("Error init glew");

    Point3df cameraPos { 0, 200.f, 0.f };
    float cameraAlpha = 0;
    float cameraBeta = 0;
    int seed = 121;

    MapGenerator map;
    map.SetSeed(seed);
    map.GenerateAllChunks(0, 0);
    
    //map.Generate();
    sf::Clock dtClock;
    // la boucle principale
    bool running = true;
    while (running) {
        float dt = dtClock.restart().asSeconds();

        // gestion des �v�nements
        sf::Event event{};
        while (window.pollEvent(event)) {
           // ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                // on stoppe le programme
                running = false;
               // ImGui::SFML::Shutdown();
            } else if (event.type == sf::Event::Resized) {
                // on ajuste le viewport lorsque la fen�tre est redimensionn�e
                glViewport(0, 0, event.size.width, event.size.height);
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        cameraPos.y += 50 * dt;
                        break;
                    case sf::Keyboard::W:
                        cameraPos.y -= 50 * dt;
                        break;
                    case sf::Keyboard::Z:
                        cameraPos.x += 50 * dt;
                        break;
                    case sf::Keyboard::S:
                        cameraPos.x -= 50 * dt;
                        break;
                    case sf::Keyboard::Q:
                        cameraPos.z -= 50 * dt;
                        break;
                    case sf::Keyboard::D:
                        cameraPos.z += 50 * dt;
                        break;
                    case sf::Keyboard::F:
                        map.m_frequency = map.m_frequency + 0.05;
                        map.GenerateAllChunks(cameraPos.x, cameraPos.z);
                        break;
                    case sf::Keyboard::C:
                        map.m_frequency = map.m_frequency - 0.05;
                        map.GenerateAllChunks(cameraPos.x, cameraPos.z);
                        break;
                    case sf::Keyboard::R:
                        map.m_redistribution = map.m_redistribution + 1;
                        map.GenerateAllChunks(cameraPos.x, cameraPos.z);
                        break;
                    case sf::Keyboard::T:
                        map.m_redistribution = map.m_redistribution - 1;
                        map.GenerateAllChunks(cameraPos.x, cameraPos.z);
                        break;
                    case sf::Keyboard::P:
                        seed++;
                        map.SetSeed(seed);
                        map.GenerateAllChunks(cameraPos.x, cameraPos.z);
                        break;
                    case sf::Keyboard::M:
                        seed--;
                        map.SetSeed(seed);
                        map.GenerateAllChunks(cameraPos.x, cameraPos.z);
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        ImGui::SFML::Shutdown();
                        return 0;
                    case sf::Keyboard::I:
                        map.terraces = map.terraces + 1;
                        map.GenerateAllChunks(0, 0);
                        break;
                    case sf::Keyboard::K:
                        map.terraces = map.terraces - 1;
                        map.GenerateAllChunks(0, 0);
                        break;
                }
            } else if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i halfWindowSize = { (int)window.getSize().x / 2, (int)window.getSize().y / 2 };

                cameraAlpha += static_cast<float>(event.mouseMove.x - halfWindowSize.x) * -0.001f;
                cameraBeta += static_cast<float>(event.mouseMove.y - halfWindowSize.y) * 0.001f;

                sf::Mouse::setPosition(halfWindowSize, window);
            }
        }

        // effacement les tampons de couleur/profondeur
        glClearColor(0, 207, 220, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Mat4<float> v = Mat4<float>::RotationX(-cameraBeta) * Mat4<float>::RotationY(-cameraAlpha) *
                        Mat4<float>::Translation(-cameraPos.x, -cameraPos.y, -cameraPos.z);

        float aspect = (float)window.getSize().x / (float)window.getSize().y;
        float fov = 45.0f / 180.0f * 3.14159265358979323846f;
        float n = 0.1f;
        float f = 500.f;
        // Matrice de projection
        auto p = Mat4f::Projection(aspect, fov, f, n);
        map.checkPlayerChunk(cameraPos.x, cameraPos.z);
        Mat4<float> vp = p * v;
        // map.Generate(static_cast<int>(cameraPos.x), static_cast<int>(cameraPos.z));
        map.Render(vp);


        glFlush();
        // termine la trame courante (en interne, �change les deux tampons de rendu)
        // ImGui::SFML::Render(window);
        window.display();
    }

    // lib�ration des ressources...

    return 0;
}

