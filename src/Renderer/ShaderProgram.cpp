#include "ShaderProgram.h"
#include <iostream>

namespace Renderer
{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint vertexShaderID;
        if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
        {
            std::cout<< "VERTESH SHADER::ERROR" << std::endl;
            return;
        }

        GLuint fragmentShaderID;
        if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
        {
            std::cout<< "VERTESH SHADER::ERROR" << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShaderID);
        glAttachShader(m_ID, fragmentShaderID);
        glLinkProgram(m_ID);

        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        else
        {
            m_IsCompiled = true;
        }
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }
    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        m_ID = shaderProgram.m_ID;
        m_IsCompiled = shaderProgram.m_IsCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_IsCompiled = false;
    }



    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_IsCompiled = shaderProgram.m_IsCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_IsCompiled = false;

        return *this;
    }



    bool ShaderProgram::CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, NULL);
        glCompileShader(shaderID);


        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
             std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            return false;
        }
    return true;
    }

    void ShaderProgram::Use() const
    {
        glUseProgram(m_ID);
    }


     
    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ID);
    }
}