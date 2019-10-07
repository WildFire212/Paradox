#include "GBufferShader.h"
#include"../core/RenderingEngine.h"
namespace Paradox {
	namespace graphics {


		GBufferShader::GBufferShader(const char * vertLoc, const char * fragLoc) : Shader(vertLoc, fragLoc)
		{

		}

		void GBufferShader::updateAllUniforms(Transform* transform, const RenderingEngine* engine, const Material* material)
		{
			this->SetUniformMat4("projection",engine->getMainCamera().getProjection());
			this->SetUniformMat4("view" , engine->getMainCamera().calculateViewMatrix()); 
			this->SetUniformMat4("model",transform->getTransformation()); 
			this->m_Material.specularIntensity = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "material.specularIntensity");
			this->m_Material.shininess = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "material.shininess");
			this->m_Material.diffuseTexture = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "material.diffuseTexture");
			material->UseMaterial(m_Material.specularIntensity, m_Material.shininess,m_Material.diffuseTexture); 
		}

		GBufferShader::~GBufferShader()
		{
		}
	}
}