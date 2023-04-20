//
// Created by Flo on 20/04/2023.
//

#include "Shader.hpp"

#include <Logger.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

GLuint Shader::LoadShaders(ShaderInfo* shaderInfo)
{
    if (shaderInfo == nullptr)
        throw std::runtime_error("ShaderInfo is null");

    GLuint program = glCreateProgram();
    auto* entry = shaderInfo;

    while(entry->type != GL_NONE)
    {
        entry->shaderId = glCreateShader(entry->type);
        auto str = ReadShader(entry->filename);
        const auto source = str.c_str();

        if (source == nullptr)
        {
            for (entry = shaderInfo; entry->type != GL_NONE; ++entry)
            {
                glDeleteShader(entry->shaderId);
                entry->shaderId = 0;
            }

            return 0;
        }

        glShaderSource(entry->shaderId, 1 , &source, nullptr);
        glCompileShader(entry->shaderId);

        GLint hasCompiled = 0;
        glGetShaderiv(entry->shaderId, GL_COMPILE_STATUS, &hasCompiled);

        if (!hasCompiled)
        {
            HandleShaderCompilationError(shaderInfo);
            return 0;
        }

        glAttachShader(program, entry->shaderId);
        ++entry;
    }

    glLinkProgram(program);
    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        HandleShaderLinkError(shaderInfo, program);
        return 0;
    }

    return program;
}

std::string Shader::ReadShader(const char* filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
        throw std::runtime_error("Filename cannot be opened");

    std::stringstream buffer;
    buffer << inputFile.rdbuf();

    inputFile.close();
    return buffer.str();
}

void Shader::HandleShaderCompilationError(ShaderInfo* shaderInfo)
{
    GLsizei length = 0;
    glGetShaderiv(shaderInfo->shaderId, GL_INFO_LOG_LENGTH, &length);
    auto* errLog = new GLchar[length + 1];
    glGetShaderInfoLog(shaderInfo->shaderId, length, &length, errLog);

    Logger::Err("Shader compilation failed: ", errLog);

    delete[] errLog;
    errLog = nullptr;
}

void Shader::HandleShaderLinkError(ShaderInfo *shaderInfo, GLuint program)
{
    GLsizei length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    auto* errLog = new GLchar[length + 1];
    glGetProgramInfoLog(program, length, &length, errLog);

    Logger::Err("Shader linking failed: ", errLog);

    delete[] errLog;
    errLog = nullptr;

    for (auto* entry = shaderInfo; entry->type != GL_NONE; ++entry)
    {
        glDeleteShader(entry->shaderId);
        entry->shaderId = 0;
    }
}
