#pragma once

#include "glm/glm.hpp"

#include <unordered_map>

namespace rendering {
	class Shader
	{
	private:
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformCache;
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, int i);
		void SetUniform2f(const std::string& name, float f0, float f1);
		void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
		void SetUniformMat4f(const std::string& name, glm::mat4& m4f);
	private:
		int GetUniformLocation(const std::string& name);
		unsigned int CompileShaderSource(unsigned int type, const std::string& source);
	};
}
