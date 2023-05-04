#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <stdexcept>
#include <valarray>
#include "Math/Matrix.hpp"
#include "SFML/Graphics/Image.hpp"
#include "Shader.h"
#include "Texture.h"


template<typename T>
class Triangle
{
    using vertex_type = vertex_struct_texture_3D<T>;

public:
    Triangle():m_texture("moche2.bmp") {};
    
    void Render(const Mat4<T>& viewProjection);


    void GenerateVertices(std::vector<float> vertices, std::vector<unsigned int> indices, int map_width, int map_height);

    ~Triangle()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    

private:
    unsigned int m_num_strips;
    unsigned int m_num_verts_per_strip;
    T m_angle = 0.0f;
    Texture m_texture;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_program;
};
