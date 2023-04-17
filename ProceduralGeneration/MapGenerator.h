#include<vector>

#include <iostream>
#include "Shape.h"
#include "ProceduralAlgo/PerlinNoise.h"
#include <gl/glew.h>
#include <math.h>
#include <cmath>
#include "../Game/Matrix.h"


class MapGenerator
{
private:
    int cols, rows;
    const int scale = 4;
    float m_angle = 0.0f;
    GLuint m_program = 0;
    int width = 50;
    int height = 50;
    std::vector<unsigned int> indices;
    std::vector<float> vertices;
    
    using Point2f = Point2D<float>;
    using Point3f = Point3D<float>;
    using Trianglef = Triangle<float>;

    const unsigned int NUM_STRIPS = width - 1;
    const unsigned int NUM_VERTS_PER_STRIP = height * 2;
    PerlinNoise perlin;
public:

    //Parameters:
    float m_frequency = 1.0f;
    //De 0 à 10
    unsigned int m_redistribution = 2;


    using Trianglef = Triangle<float>;
    using Point3f = Point3D<float>;
    std::vector<std::unique_ptr<Trianglef>> triangles;

    MapGenerator(unsigned int seed)
    {
        perlin.setSeed(seed);
    };

    template<typename T>
    void Render(const Mat4<T>& viewProjection)
    {
        
        Mat4<T> model;

        //Rotation sur l'axe Y
        model(0, 0) = std::cos(m_angle);
        model(0, 2) = std::sin(m_angle);
        model(2, 0) = -std::sin(m_angle);
        model(2, 2) = std::cos(m_angle);

        model(1, 1) = 1.0f;
        model(3, 3) = 1.0f;

        model(2, 3) = -5.0f;

        Mat4<T> mvp = viewProjection * model;

        auto mvpLocation = glGetUniformLocation(m_program, "model");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.data());
        // render the mesh triangle strip by triangle strip - each row at a time
        for (unsigned int strip = 0; strip < NUM_STRIPS; ++strip)
        {
            glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                NUM_VERTS_PER_STRIP, // number of indices to render
                GL_UNSIGNED_INT,     // index data type
                (void*)(sizeof(unsigned int)
                    * NUM_VERTS_PER_STRIP
                    * strip)); // offset to starting index
        }

    }

    void Generate()
    {            
        std::cout << "Redistribution : " << m_redistribution << std::endl;
        vertices.clear();
        indices.clear();

        for (float i = 0; i < height; i++)
        {
            for (float j = 0; j < width; j++)
            {
                double nx = i / width - 0.5, ny = j / height - 0.5;
                float e = m_frequency * perlin.noise(m_frequency * nx, m_frequency * ny)+
                          (m_frequency / 2) * perlin.noise(m_frequency * 2 * nx, m_frequency * 2 * ny)+
                          (m_frequency / 4) * perlin.noise(m_frequency * 4 * nx, m_frequency * 4 * ny)+
                          (m_frequency / 8) * perlin.noise(m_frequency * 8 * nx, m_frequency * 8 * ny)+
                          (m_frequency / 16) * perlin.noise(m_frequency * 16 * nx, m_frequency * 16 * ny)
                    ;
                e = e / (m_frequency + (m_frequency / 2) + (m_frequency / 4) +  (m_frequency/8) + (m_frequency/16));

                float elevation = pow(e, m_redistribution);

                vertices.push_back(i);
                vertices.push_back(elevation * (height / 4));
                vertices.push_back(j);
            }

        }


        for (unsigned int i = 0; i < height - 1; i++)       // for each row a.k.a. each strip
        {
            for (unsigned int j = 0; j < width; j++)      // for each column
            {
                for (unsigned int k = 0; k < 2; k++)      // for each side of the strip
                {
                    indices.push_back(j + width * (i + k));
                }
            }
        }
        
        ShaderInfo shader[] = {
                { GL_VERTEX_SHADER, "triangles.vert" },
                { GL_FRAGMENT_SHADER, "triangles.frag" },
                { GL_NONE, nullptr }
        };

        auto program = Shader::loadShaders(shader);
        glUseProgram(program);
        m_program = program;

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        /*       for (auto& triangle : triangles)
                   triangle->render(viewProjection);*/
        GLuint terrainVAO, terrainVBO, terrainEBO;
        glGenVertexArrays(1, &terrainVAO);
        glBindVertexArray(terrainVAO);

        glGenBuffers(1, &terrainVBO);
        glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
        glBufferData(GL_ARRAY_BUFFER,
            vertices.size() * sizeof(float),       // size of vertices buffer
            &vertices[0],                          // pointer to first element
            GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &terrainEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(unsigned int), // size of indices buffer
            &indices[0],                           // pointer to first element
            GL_STATIC_DRAW);

        glBindVertexArray(terrainVAO);
    }
};