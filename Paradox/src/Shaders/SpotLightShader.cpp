#include "SpotLightShader.h"
#include"../core/RenderingEngine.h"
namespace Paradox {
	namespace graphics {


		SpotLightShader::SpotLightShader(const char* vertLoc, const char* fragLoc) : Shader(vertLoc, fragLoc)
		{
		}


		void SpotLightShader::updateAllUniforms( Transform* transform, const RenderingEngine* engine, const Material* material)
		{
			calcLightLocations();
			//transform
			this->SetUniform3f("eyePosition", engine->getMainCamera().getPosition());
			//lighting 
			this->SetUniform1i("gPosition", 0);
			this->SetUniform1i("gNormal", 1);
			this->SetUniform1i("gAlbedoSpec", 2);
			
		}

		const SpotLightShader::SpotLightLocation & SpotLightShader::getSpotLightLocation()
		{
			// TODO: insert return statement here
			return spotLightLoc; 
		}


		SpotLightShader::~SpotLightShader()
		{
		}
		void SpotLightShader::calcLightLocations()
		{
			spotLightLoc.ColorLocation = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "spotLight.base.base.colour");
			spotLightLoc.ambientIntensityLocation = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "spotLight.base.base.ambientIntensity");
			spotLightLoc.diffuseIntensityLocation = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "spotLight.base.base.diffuseIntensity");
			spotLightLoc.positionLocation = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "spotLight.base.position");
			spotLightLoc.exp = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "spotLight.base.exponent");
			spotLightLoc.cons = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "spotLight.base.constant");
			spotLightLoc.lin = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "spotLight.base.linear");
			spotLightLoc.direction = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "spotLight.direction");
			spotLightLoc.edge = glGetUniformLocation(m_ShaderResource->getShaderProgram(), "spotLight.edge");
		}

	}
}
