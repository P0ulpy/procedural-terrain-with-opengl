//
// Created by Flo on 29/04/2023.
//

#pragma once

#include <vector>

#include <gl/glew.h>

#include <Texture/Texture.hpp>
#include <Renderable/IRenderable.hpp>

class Chunk : public IRenderable
{
public:
    constexpr static int32_t SIZE = 128;

    Chunk();
    ~Chunk() override = default;

    void Generate(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, GLuint program);

    void Load() override;
    void Render(Camera& camera) override;
    void Cleanup() override;

private:
    GLuint VAO {}, VBO {}, EBO {};
    std::vector<float> m_vertices {};
    std::vector<uint32_t> m_indices {};

    GLuint m_program {};
};
