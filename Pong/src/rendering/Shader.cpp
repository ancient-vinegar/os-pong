#include "Shader.h"

#include "glad/glad.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

rendering::Shader::Shader(const std::string& filepath)
    : m_RendererID(0)
{
    std::ifstream stream(filepath);
    unsigned int type = 0;
    std::unordered_map<unsigned int, std::stringstream> sources;
    std::list<unsigned int> shaders;
    std::string line;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = GL_VERTEX_SHADER;
                if (sources.find(GL_VERTEX_SHADER) != sources.end()) {
                    std::cout << "Multiple vertex shader declarations!]\n\t" << filepath << std::endl;
                    return;
                }
                shaders.push_back(type);
            }
            else if (line.find("fragment") != std::string::npos) {
                type = GL_FRAGMENT_SHADER;
                if (sources.find(GL_FRAGMENT_SHADER) != sources.end()) {
                    std::cout << "Multiple fragment shader declarations!]\n\t" << filepath << std::endl;
                    return;
                }
                shaders.push_back(type);
            }
            else if (line.find("geometry") != std::string::npos) {
                type = GL_GEOMETRY_SHADER;
                if (sources.find(GL_GEOMETRY_SHADER) != sources.end()) {
                    std::cout << "Multiple geometry shader declarations!]\n\t" << filepath << std::endl;
                    return;
                }
                shaders.push_back(type);
            }
            else if (line.find("tess eval") != std::string::npos) {
                type = GL_TESS_EVALUATION_SHADER;
                if (sources.find(GL_TESS_EVALUATION_SHADER) != sources.end()) {
                    std::cout << "Multiple tess evaluation shader declarations!]\n\t" << filepath << std::endl;
                    return;
                }
                shaders.push_back(type);
            }
            else if (line.find("tess ctrl") != std::string::npos) {
                type = GL_TESS_CONTROL_SHADER;
                if (sources.find(GL_TESS_CONTROL_SHADER) != sources.end()) {
                    std::cout << "Multiple tess control shader declarations!]\n\t" << filepath << std::endl;
                    return;
                }
                shaders.push_back(type);
            }
            else if (line.find("compute") != std::string::npos) {
                type = GL_COMPUTE_SHADER;
                if (sources.find(GL_COMPUTE_SHADER) != sources.end()) {
                    std::cout << "Multiple compute shader declarations!]\n\t" << filepath << std::endl;
                    return;
                }
                shaders.push_back(type);
            }
        }
        else {
            sources[type] << line << '\n';
        }
    }

    unsigned int program = glCreateProgram();
    std::list<unsigned int> compiledShaders;
    while (!shaders.empty()) {
        unsigned int cShader = CompileShaderSource(shaders.front(), sources[shaders.front()].str());
        glAttachShader(program, cShader);
        compiledShaders.push_back(cShader);
        shaders.pop_front();
    }

    glLinkProgram(program);
    glValidateProgram(program);

    while (!compiledShaders.empty()) {
        glDeleteShader(compiledShaders.front());
        compiledShaders.pop_front();
    }

    m_RendererID = program;
}

rendering::Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void rendering::Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void rendering::Shader::Unbind() const
{
    glUseProgram(0);
}

void rendering::Shader::SetUniform1i(const std::string& name, int i)
{
    glUniform1i(GetUniformLocation(name), i);
}

void rendering::Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
    glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
}

void rendering::Shader::SetUniformMat4f(const std::string& name, glm::mat4& m4f)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &m4f[0][0]);
}

int rendering::Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformCache.find(name) != m_UniformCache.end())
        return m_UniformCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout << "Uniform {" << name << "} doesn't exist!" << std::endl;
    m_UniformCache[name] = location;
    return location;
}

unsigned int rendering::Shader::CompileShaderSource(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile\n\t" << (type == GL_VERTEX_SHADER ? "VERTEX" : type == GL_FRAGMENT_SHADER ? "FRAGMENT" : type == GL_GEOMETRY_SHADER ? "GEOMETRY" : type == GL_TESS_EVALUATION_SHADER ? "TESS_EVAL" : type == GL_TESS_CONTROL_SHADER ? "TESS_CTRL" : type == GL_COMPUTE_SHADER ? "COMPUTE" : "[ERROR]") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
