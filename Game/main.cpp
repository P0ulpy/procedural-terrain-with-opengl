#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "GL/glew.h"
#include "SFML/OpenGL.hpp"
#include "Shaders/Shader.h"

#include <array>
#include <fstream>


template<typename T>
struct Point2d {
    explicit Point2d(const T &_x = 0, const T &_y = 0)
            : x(_x), y(_y) {}

    Point2d(const Point2d &pt)
            : x(pt.x), y(pt.y) {}

    T x;
    T y;
};

template<typename T>
struct Point3d {
    explicit Point3d(const T &_x = 0, const T &_y = 0, const T &_z = 0)
            : x(_x), y(_y), z(_z) {}

    Point3d(const Point3d &pt)
            : x(pt.x), y(pt.y), z(pt.z) {}

    T x;
    T y;
    T z;
};

template<typename Type>
struct Mat4 {
    using T = Type;

    Mat4() {
        for (int i = 0; i < 16; ++i) m_data[i] = 0;
    }

    T &operator()(int line, int col) { return m_data[line + col * 4]; }

    const T &operator()(int line, int col) const { return m_data[line + col * 4]; }

    std::array<Type, 16> m_data;
};

template<typename Type>
Mat4<Type> operator*(const Mat4<Type> &op1, const Mat4<Type> &op2) {
    Mat4<Type> result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k)
                result(i, j) += op1(i, k) * op2(k, j);
        }
    }
    return result;
}

template<typename Type>
struct Color {
    Color(const Type &r_, const Type &g_, const Type &b_, const Type &a_) : r(r_), g(g_), b(b_), a(a_) {}

    Type r = 0;
    Type g = 0;
    Type b = 0;
    Type a = 0;
};

template<typename Type>
struct vertex_struct {
    Point3d<Type> p;
    Point2d<Type> t;
};

struct Texture {
    Texture() {
        std::string path = "Assets/Textures/test.png";

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        sf::Image image;
        image.loadFromFile(path);

        auto size = image.getSize();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void bind() const {
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }

    GLuint m_texture{};
};

struct TextureRed {
    TextureRed() {
        std::string path = "Assets/Textures/red.png";

        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        sf::Image image;
        image.loadFromFile(path);

        auto size = image.getSize();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void bind() const {
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }

    GLuint m_texture{};
};

template<typename Type>
class Triangle {
public:

    Triangle(const vertex_struct<Type> &p0, const vertex_struct<Type> &p1, const vertex_struct<Type> &p2)
            : m_vao(0), m_vbo(0), m_points{{p0, p1, p2}} {
        load();
    }

    ~Triangle() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    void load() {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points.data(), GL_STATIC_DRAW);

        ShaderInfo shaders[] = {
                {GL_VERTEX_SHADER,   "Assets/Shaders/triangles.vert"},
                {GL_FRAGMENT_SHADER, "Assets/Shaders/triangles.frag"},
                {GL_NONE,            nullptr}
        };

        m_program = Shader::loadShaders(shaders);
        glUseProgram(m_program);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_struct<Type>), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_struct<Type>),
                              (char *) nullptr + sizeof(vertex_struct<Type>::p));
        glEnableVertexAttribArray(1);
    }

    void render(const Mat4<Type> &VP) {
        glBindVertexArray(m_vao);
        Color<Type> c{1.0, 0.0, 0.0, 1.0};
        GLuint mySuperColorLocation = glGetUniformLocation(m_program, "mySuperColor");
        glUniform4f(mySuperColorLocation, c.r, c.g, c.b, c.a);

        Mat4<Type> Model;
        Model(0, 0) = std::cos(m_angle);
        Model(0, 2) = std::sin(m_angle);
        Model(2, 0) = -std::sin(m_angle);
        Model(2, 2) = std::cos(m_angle);

        Model(1, 1) = 1.f;
        Model(3, 3) = 1.f;

        Model(2, 3) = -5.0f;

        Mat4<Type> MVP = VP * Model;

        GLuint MVPLocation = glGetUniformLocation(m_program, "MVP");
        glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &MVP.m_data[0]);

        m_texture.bind();
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_points.size()));
    }

    void render2(const Mat4<Type> &VP) {
        glBindVertexArray(m_vao);
        Color<Type> c{1.0, 0.0, 0.0, 0.2};
        GLuint mySuperColorLocation = glGetUniformLocation(m_program, "mySuperColor");
        glUniform4f(mySuperColorLocation, c.r, c.g, c.b, c.a);

        Mat4<Type> Model;
        Model(0, 0) = std::cos(m_angle) + 1.f;
        Model(0, 2) = std::sin(m_angle);
        Model(2, 0) = -std::sin(m_angle);
        Model(2, 2) = std::cos(m_angle);

        Model(1, 1) = 3.f;
        Model(3, 3) = 1.f;

        Model(2, 3) = -10.0f;

        Mat4<Type> MVP = VP * Model;

        GLuint MVPLocation = glGetUniformLocation(m_program, "MVP");
        glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &MVP.m_data[0]);

        m_textureRed.bind();
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_points.size()));
    }

    void update() {
        m_angle += 0.0025f;
    }

private:
    Type m_angle = 0;
    Texture m_texture;
    TextureRed m_textureRed;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_program{};
    std::array<vertex_struct<Type>, 3> m_points;
};

int main() {
    const sf::ContextSettings settings(24, 8, 4, 4, 6);

    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

    using Point2f = Point2d<float>;
    using Point3f = Point3d<float>;
    using Trianglef = Triangle<float>;

    // fucking lines of hell
    glewExperimental = GL_TRUE;
    if (glewInit())
        throw std::runtime_error("Error");

    vertex_struct<float> p0{Point3f{-0.9f, -0.9f, 0.f}, Point2f{-1.f, -1.f}};
    vertex_struct<float> p1{Point3f{0.9f, -0.9f, 0.f}, Point2f{1.f, -1.f}};
    vertex_struct<float> p2{Point3f{0.9f, 0.9f, 0.f}, Point2f{1.f, 1.f}};

    Trianglef triangle(p0, p1, p2);
    Trianglef triangle2(p0, p1, p2);

    bool running = true;
    while (running) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            } else if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Mat4<float> V;
        V(0, 0) = 1.f;
        V(1, 1) = 1.f;
        V(2, 2) = 1.f;
        V(3, 3) = 1.f;

        Mat4<float> P;
        float aspect = 1.f;
        float fov = 45.f / 180.f * 3.141592f;
        float n = 0.1f;
        float f = 100.f;
        P(0, 0) = 1.f / (aspect * std::tan(fov / 2.f));
        P(1, 1) = 1.f / (std::tan(fov / 2.f));
        P(2, 2) = -(f + n) / (f - n);
        P(2, 3) = -(2.f * f * n) / (f - n);
        P(3, 2) = -1.f;

        Mat4<float> VP = P * V;

        triangle.update();
        triangle.render(VP);

        triangle2.update();
        triangle2.render2(VP);
        glFlush();

        window.display();
    }
    return 0;
}