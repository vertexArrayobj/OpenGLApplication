#pragma once

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;

	std::unordered_map<std::string, int> m_UniformLocationCache;

	int GetUniformLocation(const std::string& uniform);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetShaderUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetShaderUniform1i(const std::string& name, int v);
	void SetShaderUniformMat4f(const std::string& name, const glm::mat4& matrix);
};
