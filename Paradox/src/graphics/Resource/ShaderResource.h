#pragma once
#include<GL/glew.h>
#include<string>
#include<vector>

namespace Paradox {
	namespace graphics {

class ShaderResource

{
private: 
	GLuint m_ShaderProgram;
	std::vector<std::string> m_UniformNames;
	std::vector<std::string> m_UniformTypes; 
public:
	ShaderResource() {}
	~ShaderResource() {}

	void setShaderProgram(GLuint shaderProgram)
	{
		m_ShaderProgram = shaderProgram;
	}

	//uniform names 
	void addUniformName(std::string name) {
		m_UniformNames.push_back(name);
	}
	inline const std::vector<std::string> getUniformNames() {
		return m_UniformNames;
	}
	//uniform types 
	void addUniformType(std::string type) {
		m_UniformTypes.push_back(type);
	}
	inline const std::vector<std::string> getUniformTypes() {
		return m_UniformTypes;
	}


	void printContent()
	{
		for (int i = 0; i < m_UniformNames.size(); i++)
		{
			std::cout << "uniform type is-" << m_UniformTypes[i] << "-content is -" << m_UniformNames[i] << std::endl; 
		}
	}
	
	inline const GLuint getShaderProgram()
	{
		return m_ShaderProgram;
	}

};

} }
