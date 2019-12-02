#pragma once
#include "PointLight.h"
#include"../Shaders/SpotLightShader.h"
namespace Paradox {
	namespace component
	{

		class SpotLight :
			public PointLight
		{
		public:


			SpotLight(GLfloat red, GLfloat green, GLfloat blue,
				GLfloat aIntensity, GLfloat dIntensity,
				maths::vec3 pos,
				maths::vec3 direction,
				GLfloat con, GLfloat lin, GLfloat exp,
				GLfloat edg);

			void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
				GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
				GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
				GLuint edgeLocation);
			void renderLight(RenderingEngine& renderingEngine) override;
			void SetFlash(maths::vec3 pos, maths::vec3 dir);

			~SpotLight();

		private:
			maths::vec3 direction;

			GLfloat edge, procEdge;
		};

	}
}