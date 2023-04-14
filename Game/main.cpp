#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <array>
//#include "Shader.h"
#include "MapGenerator.h"


int main()
{
    // set version of opengl to 4.6
    const sf::ContextSettings context_settings(24, 8, 4, 4, 6);
    // cr�e la fen�tre
    sf::Window window(sf::VideoMode(800, 800), "OpenGL", sf::Style::Default, context_settings);
    window.setVerticalSyncEnabled(true);

    // activation de la fen�tre
    window.setActive(true);

    // fucking lines of hell
    glewExperimental = GL_TRUE;
    if (glewInit())
        throw std::runtime_error("Error init glew");

    // chargement des ressources, initialisation des �tats OpenGL, ...
    using Point2f = Point2d<float>;
    using Trianglef = Triangle<float>;
    std::vector<Trianglef*> triangles;

    Point2f p0 { -1, 1 };
    Point2f p1 { 0, 1 };
    Point2f p2 { -1,0 };
    Point2f p3 { 0,0 };

    Trianglef triangle{ p0, p1, p2 };
    Trianglef triangle2{ p1, p2, p3 };

    triangles.push_back(&triangle);
    triangles.push_back(&triangle2);
    MapGenerator map = MapGenerator(800, 800);
    map.Generate();

    // la boucle principale
    bool running = true;
    while (running)
    {
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
        }

        // effacement les tampons de couleur/profondeur
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // dessin...
        // triangle.render();
        map.Render();

        glFlush();
        // termine la trame courante (en interne, �change les deux tampons de rendu)
        window.display();
    }

    // lib�ration des ressources...

    return 0;
}

