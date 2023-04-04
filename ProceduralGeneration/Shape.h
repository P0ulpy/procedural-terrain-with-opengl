#include <GL/glew.h>

template<typename T>
struct Point2d
{
    explicit Point2d(const T x = 0, const T y = 0) : x(x), y(y) {}
    Point2d(const Point2d& pt) : x(pt.x), y(pt.y) {}

    T x;
    T y;
};

template<typename T>
class Triangle
{
public:
    using point_type = Point2d<T>;

    Triangle(point_type pt1, point_type pt2, point_type pt3) : m_vao(0), m_vbo(0), m_vertices({ pt1, pt2, pt3 })
    {
        load();
    }
    explicit Triangle(const std::array<point_type, 3>& points) : m_vao(0), m_vbo(0), m_vertices(points)
    {
        load();
    }

    ~Triangle()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    void load()
    {
        //we want only one buffer with the id generated and stored in m_vao
        glGenVertexArrays(1, &m_vao);
        // create a new active VAO
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);

        /*ShaderInfo shaders[] = {
            { GL_VERTEX_SHADER, "triangles.vert"},
            { GL_FRAGMENT_SHADER, "triangles.frag"},
            { GL_NONE, nullptr}
        };

        const auto program = Shader::loadShaders(shaders);
        glUseProgram(program);

        auto canvasSizeUniform = glGetUniformLocation(program, "canvasSize");*/
        //glUniform2f(canvasSizeUniform, 800, 600);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // le 2 parce qu'on a 2 valeurs par points
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
    }

    void release() {}

    void render()
    {
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertices.size()));
    }

private:
    GLuint m_vao;
    GLuint m_vbo;
    std::array<point_type, 3> m_vertices;
};

