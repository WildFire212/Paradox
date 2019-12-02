#include "DirectionalLight.h"
namespace Paradox {
	namespace component {



		DirectionalLight::DirectionalLight() : Light() {

		}
		DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, maths::vec3 dir) : Light(red, green, blue, aIntensity, dIntensity)
		{
			direction = dir;
			m_Shader = new Shader("src/Shaders/GLSLShaders/DirectLightShader.vert","src/Shaders/GLSLShaders/DirectLightShader.frag" ); 
			m_ValueMap->addVector3("direction", maths::vec3(direction.x, direction.y, direction.z)); 
			m_ValueMap->addVector3("colour", maths::vec3(color.x, color.y, color.z));
			m_ValueMap->addFloat("ambientIntensity", ambientIntensity);
			m_ValueMap->addFloat("diffuseIntensity", diffuseIntensity);

		}

		void DirectionalLight::renderLight(RenderingEngine & renderingEngine)
		{
			//DirectLightShader* shader = static_cast<DirectLightShader*>(m_Shader);
			m_Shader->bind();
			m_Shader->updateAllUniforms(nullptr, &renderingEngine, nullptr);
			//this->UseLight(shader->getDirectionalLightLocations().ColorLocation,
			//	shader->getDirectionalLightLocations().ambientIntensityLocation,
			//	shader->getDirectionalLightLocations().diffuseIntensityLocation,
			//	shader->getDirectionalLightLocations().directionLocation);
		
		}

		void DirectionalLight::UseLight(GLuint aColorLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint directionLocation)
		{
			
			glUniform3f(aColorLocation, color.x, color.y, color.z);
			glUniform1f(aIntensityLocation, ambientIntensity);
			glUniform3f(directionLocation, direction.x, direction.y, direction.z);
			glUniform1f(dIntensityLocation, diffuseIntensity);
		}
		
		DirectionalLight::~DirectionalLight()
		{
		}
	}
}