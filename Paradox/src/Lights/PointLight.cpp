#include "PointLight.h"
namespace Paradox {
	namespace component
	{


		PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
			GLfloat aIntensity, GLfloat dIntensity,
			maths::vec3 pos, GLfloat cons, GLfloat lin, GLfloat exp) : Light(red, green, blue, aIntensity, dIntensity)
		{
			position = pos;
			exponent = exp;
			linear = lin;
			constant = cons;
			m_Shader = new Shader("src/Shaders/GLSLShaders/DirectLightShader.vert", "src/Shaders/GLSLShaders/PointLightShader.frag");
			m_ValueMap->addVector3("position", maths::vec3(position.x, position.y, position.z));
			m_ValueMap->addFloat("exponent", exponent);
			m_ValueMap->addFloat("linear", linear);
			m_ValueMap->addFloat("constant",constant);
			m_ValueMap->addVector3("colour", maths::vec3(color.x, color.y, color.z));
			m_ValueMap->addFloat("ambientIntensity", ambientIntensity);
			m_ValueMap->addFloat("diffuseIntensity", diffuseIntensity);

		
		}

		void PointLight::UseLight(GLuint aColorLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint positionLocation,
			GLuint expLocation, GLuint linLocation, GLuint consLocation)
		{
			glUniform3f(aColorLocation, color.x, color.y, color.z);
			glUniform1f(aIntensityLocation, ambientIntensity);
			glUniform1f(dIntensityLocation, diffuseIntensity);
			glUniform3f(positionLocation, position.x, position.y, position.z);
			glUniform1f(expLocation, exponent);
			glUniform1f(linLocation, linear);
			glUniform1f(consLocation, constant);

		}

		void PointLight::renderLight(RenderingEngine & renderingEngine)
		{
			m_Shader->bind(); 
			m_Shader->updateAllUniforms(nullptr, &renderingEngine, nullptr);
			//this->UseLight(shader->getPointLightLocations().ColorLocation, shader->getPointLightLocations().ambientIntensityLocation,
			//	shader->getPointLightLocations().diffuseIntensityLocation, shader->getPointLightLocations().positionLocation,
			//	shader->getPointLightLocations().exp, shader->getPointLightLocations().lin, shader->getPointLightLocations().cons);
			
		}

		PointLight::~PointLight()
		{
		}
	}
}