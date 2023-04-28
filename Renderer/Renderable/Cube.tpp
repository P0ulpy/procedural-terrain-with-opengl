//
// Created by Flo on 20/04/2023.
//

#include "Color/Color.hpp"
#include "Shader/Shader.hpp"

template<typename T>
struct vertex_struct_cube
{
    vertex_struct_cube(const Point3d<T>& p, const Color<T>& c)
            : p(p)
            , c(c)
    {}

    Point3d<T> p;
    Color<T> c;
};

template<typename T>
Cube<T>::Cube()
{

}

template<typename T>
Cube<T>::~Cube()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

template<typename T>
void Cube<T>::Load()
{
    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    Point3d<T> P000 = { -1, -1, -1 };
    Point3d<T> P001 = { -1, -1, +1 };
    Point3d<T> P010 = { -1, +1, -1 };
    Point3d<T> P011 = { -1, +1, +1 };
    Point3d<T> P100 = { +1, -1, -1 };
    Point3d<T> P101 = { +1, -1, +1 };
    Point3d<T> P110 = { +1, +1, -1 };
    Point3d<T> P111 = { +1, +1, +1 };

    Color<T> vr = { 1, 0, 0, 1 }; Color<T> vg = { 0, 1, 0, 1 }; Color<T> vb = { 0, 0, 1, 1 };
    Color<T> ar = { 0, 1, 1, 1 }; Color<T> ag = { 1, 0, 1, 1 }; Color<T> ab = { 1, 1, 0, 1 };

    using vt = vertex_struct_cube<T>;

    std::array<vt, 3 * 12> points = {
            // Face 1
            vt{ P000, vr }, vt{ P001, vr }, vt{ P011, vr },
            vt{ P000, vr }, vt{ P011, vr }, vt{ P010, vr },
            // Face 2
            vt{ P100, vg }, vt{ P101, vg }, vt{ P111, vg },
            vt{ P100, vg }, vt{ P111, vg }, vt{ P110, vg },
            // Face 3
            vt{ P000, vb }, vt{ P001, vb }, vt{ P101, vb },
            vt{ P000, vb }, vt{ P101, vb }, vt{ P100, vb },
            // Face 4
            vt{ P010, vb }, vt{ P011, vb }, vt{ P111, vb },
            vt{ P010, vb }, vt{ P111, vb }, vt{ P110, vb },
            // Face 5
            vt{ P000, vb }, vt{ P010, vb }, vt{ P110, vb },
            vt{ P000, vb }, vt{ P110, vb }, vt{ P100, vb },
            // Face 6
            vt{ P001, ag }, vt{ P011, ag }, vt{ P111, ag },
            vt{ P001, ag }, vt{ P111, ag }, vt{ P101, ag },
    };

    m_nVertices = points.size();

    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points.data(), GL_STATIC_DRAW);

    ShaderInfo shader[] = {
            { GL_VERTEX_SHADER, "cube.vert" },
            { GL_FRAGMENT_SHADER, "cube.frag" },
            { GL_NONE, nullptr }
    };

    auto program = Shader::LoadShaders(shader);
    glUseProgram(program);
    m_program = program;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_struct_cube<T>), 0); //Pour 3D
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_struct_cube<T>), (char*)(0) + sizeof(vertex_struct_cube<T>::p));
    glEnableVertexAttribArray(1);

    glEnable(GL_DEPTH_TEST);
}

template<typename T>
void Cube<T>::Render(Camera& camera)
{
    glBindVertexArray(m_vao);

    // TODO : Move me in Update
    m_angle += 0.00025f;

    Mat4<T> model = Mat4<T>::RotationY(m_angle);
    model(2, 3) = -5.0f;

    Mat4<T> mvp = camera.GetViewProjectionMatrix() * model;

    auto mvpLocation = glGetUniformLocation(m_program, "model");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.Data());

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_nVertices));
}