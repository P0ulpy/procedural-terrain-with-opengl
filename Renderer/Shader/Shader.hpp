//
// Created by Flo on 20/04/2023.
//

#pragma once

#include <string>
#include <gl/glew.h>

struct ShaderInfo
{
    unsigned int type;
    const char* filename;
    unsigned int shaderId;
};

struct Shader
{
    static GLuint LoadShaders(ShaderInfo* shaderInfo);
    static void DestroyShaders(ShaderInfo* shaderInfo);

private:
    static std::string ReadShader(const char* filename);
    static void HandleShaderCompilationError(ShaderInfo* shaderInfo);
    static void HandleShaderLinkError(ShaderInfo* shaderInfo, GLuint program);
};
