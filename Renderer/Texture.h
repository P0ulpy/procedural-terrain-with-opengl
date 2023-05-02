#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <string>
#include <stdexcept>
#include "../Game/Matrix.h"
#include "SFML/Graphics/Image.hpp"

template<typename T>
struct vertex_struct_texture {
    Point2D<T> p;
    Point2D<T> t;
};

template<typename T>
struct vertex_struct_texture_3D {
    Point3D<T> p;
    Point2D<T> t;
};

struct Texture {
    explicit Texture(const std::string &filename) : m_texture(0) {
        load(filename);
    }

    ~Texture() {
        glDeleteTextures(1, &m_texture);
    }

    void load(const std::string &filename) {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (!m_image.loadFromFile(filename))
            throw std::runtime_error("Cannot load texture");

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(m_image.getSize().x),
                     static_cast<GLsizei>(m_image.getSize().y), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.getPixelsPtr());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void bind() const {
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }

    void unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    sf::Image m_image;

    const sf::Image &getImage() const {
        return m_image;
    }

    GLuint m_texture;
};
