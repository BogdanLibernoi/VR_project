#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer
{
    class ShaderProgram
    {
        public:
            ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
            
            ShaderProgram() = delete;
            ShaderProgram(ShaderProgram&) = delete;

            ShaderProgram(ShaderProgram&& shaderProgram) noexcept;


            ShaderProgram& operator=(const ShaderProgram&) = delete;
            ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;


            bool IsCompiled() const {return m_IsCompiled;}
            void Use() const;

            ~ShaderProgram();

        private:
            bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);

            bool m_IsCompiled = false;
            GLuint m_ID = 0;
    };
}
