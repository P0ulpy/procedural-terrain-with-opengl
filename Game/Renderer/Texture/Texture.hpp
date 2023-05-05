#pragma once

#include <string>
#include <stdexcept>

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>

#include <Math/Matrix.hpp>

struct Texture
{
    Texture() = default;

    explicit Texture(const std::string &filename) : m_texture(0)
    {
        Load(filename);
    }

    ~Texture() {
        glDeleteTextures(1, &m_texture);
    }

    void Load(const std::string &filename) {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (!m_image.loadFromFile(filename))
            throw std::runtime_error("Cannot Load texture");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(m_image.getSize().x),
                     static_cast<GLsizei>(m_image.getSize().y), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.getPixelsPtr());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Bind() const {
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }

    static void Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    [[nodiscard]] const sf::Image &GetImage() const {
        return m_image;
    }

private:
    sf::Image m_image;
    GLuint m_texture { 0 };
};
