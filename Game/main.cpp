#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <array>
#include "Matrix.h"
//#include "Shader.h"
#include "MapGenerator.h"


int main()
{
    using Point3f = Point3D<float>;
    // set version of opengl to 4.6
    const sf::ContextSettings context_settings(24, 8, 4, 4, 6);
    // cr�e la fen�tre
    sf::Window window(sf::VideoMode(1920, 1080), "OpenGL", sf::Style::Fullscreen, context_settings);
    window.setVerticalSyncEnabled(true);

    // activation de la fen�tre
    window.setActive(true);

    // fucking lines of hell
    glewExperimental = GL_TRUE;
    if (glewInit())
        throw std::runtime_error("Error init glew");

    // chargement des ressources, initialisation des �tats OpenGL, ...
    using Point2f = Point2D<float>;
    using Trianglef = Triangle<float>;
    std::vector<Trianglef*> triangles;

    Point3f cameraPos{ 0.f, 0.f, 0.f };
    float cameraAlpha = 0;
    float cameraBeta = 0;

    MapGenerator map(50,50);
    map.setSeed(153);

    map.Generate();
    //map.Generate();
    sf::Clock dtClock;
    // la boucle principale
    bool running = true;
    while (running)
    {
        float dt = dtClock.restart().asSeconds();
        // gestion des �v�nements
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
            {
                // on stoppe le programme
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // on ajuste le viewport lorsque la fen�tre est redimensionn�e
                glViewport(0, 0, event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Space:
                    cameraPos.y += 10 * dt;
                    break;
                case sf::Keyboard::LShift:
                    cameraPos.y -= 10 * dt;
                    break;
                case sf::Keyboard::Z:
                    cameraPos.x += 10 * dt;
                    break;
                case sf::Keyboard::S:
                    cameraPos.x -= 10 * dt;
                    break;
                case sf::Keyboard::F:
                    map.m_frequency = map.m_frequency + 0.1;
                    map.Generate();
					break;
                case sf::Keyboard::C:
                    map.m_frequency = map.m_frequency - 0.1;
                    map.Generate();
                    break;
                case sf::Keyboard::R:
                    map.m_redistribution = map.m_redistribution + 1;
                    map.Generate();
                    break;
                case sf::Keyboard::T:
                    map.m_redistribution = map.m_redistribution - 1;
                    map.Generate();
                    break;

                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                cameraAlpha += (event.mouseMove.x - 400) * -0.001f;
                cameraBeta += (event.mouseMove.y - 300) * 0.001f;

                sf::Mouse::setPosition(sf::Vector2i(400, 300), window);
            }
        }

        // effacement les tampons de couleur/profondeur
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Mat4<float> v = Mat4<float>::rotationX(-cameraBeta) * Mat4<float>::rotationY(-cameraAlpha) * Mat4<float>::translation(-cameraPos.x, -cameraPos.y, -cameraPos.z);

        float aspect = 800.f / 600.f;
        float fov = 45.0f / 180.0f * 3.14159265358979323846f;
        float n = 0.1f;
        float f = 100.0f;
        // Matrice de projection
        auto p = Mat4<float>::projection(aspect, fov, f, n);

        Mat4<float> vp = p * v;

        map.Render(vp);


        glFlush();
        // termine la trame courante (en interne, �change les deux tampons de rendu)
        window.display();
    }

    // lib�ration des ressources...

    return 0;
}

