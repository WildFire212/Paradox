#include "SpotLight.h"
namespace Paradox {
	namespace component
	{

		SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue,
			GLfloat aIntensity, GLfloat dIntensity, glm::vec3 pos,
			glm::vec3 dir,
			GLfloat con, GLfloat lin, GLfloat exp,
			GLfloat edg) : PointLight(red, green, blue, aIntensity, dIntensity, pos, con, lin, exp)
		{
			direction = normalize(dir);

			edge = edg;
			procEdge = cosf(glm::radians(edge));

			m_Shader = new SpotLightShader("src/Shaders/GLSLShaders/DirectLightShader.vert", "src/Shaders/GLSLShaders/SpotLightShader.frag");
		}

		void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
			GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
			GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
			GLuint edgeLocation)
		{
			glUniform3f(ambientColourLocation, color.x, color.y, color.z);
			glUniform1f(ambientIntensityLocation, ambientIntensity);
			glUniform1f(diffuseIntensityLocation, diffuseIntensity);

			glUniform3f(positionLocation, position.x, position.y, position.z);
			glUniform1f(constantLocation, constant);
			glUniform1f(linearLocation, linear);
			glUniform1f(exponentLocation, exponent);

			glUniform3f(directionLocation, direction.x, direction.y, direction.z);
			glUniform1f(edgeLocation, procEdge);
		}

		void SpotLight::renderLight(RenderingEngine & renderingEngine)
		{	SpotLightShader* shader = static_cast<SpotLightShader*>(m_Shader);
		shader->bind(); 
		shader->updateAllUniforms(nullptr, &renderingEngine, nullptr);
		this->UseLight(shader->getSpotLightLocation().ambientIntensityLocation,
			shader->getSpotLightLocation().ColorLocation, shader->getSpotLightLocation().diffuseIntensityLocation,
			shader->getSpotLightLocation().positionLocation, shader->getSpotLightLocation().direction, shader->getSpotLightLocation().cons,
			shader->getSpotLightLocation().lin, shader->getSpotLightLocation().exp, shader->getSpotLightLocation().edge);
		}

		void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
		{
			position = pos;
			direction = dir;
		}

		SpotLight::~SpotLight()
		{
		}
	}
}