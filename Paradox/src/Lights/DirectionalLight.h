#pragma once
#include "Light.h"
namespace Paradox {
	namespace component {

		class DirectionalLight :
			public Light
		{
		public:
			DirectionalLight();
			DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, glm::vec3 dir);
			void renderLight(RenderingEngine& renderingEngine) override; 
			void UseLight(GLuint aColorLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint directionLocation);
			~DirectionalLight();
		private:
			glm::vec3 direction;
			
		};

	}
}