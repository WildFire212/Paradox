#pragma once
#include"Shader.h"
namespace Paradox {
	namespace graphics {
		class RenderingEngine; 
		class SpotLightShader : public Shader
		{
		private: 
			struct {
				GLuint ColorLocation;
				GLuint ambientIntensityLocation;
				GLuint diffuseIntensityLocation;
			}light;
			struct SpotLightLocation
			{
				GLuint ColorLocation;
				GLuint ambientIntensityLocation;
				GLuint diffuseIntensityLocation;
				GLuint positionLocation;
				GLuint lin;
				GLuint cons;
				GLuint exp;
				GLuint direction;
				GLuint edge;
			}   spotLightLoc;
		public:
			SpotLightShader(const char* vertLoc, const char* fragLoc);
			void updateAllUniforms( Transform* transform, const RenderingEngine* engine, const Material* material) override;
			auto getSpotLightLocation() -> const SpotLightLocation&; 
			~SpotLightShader();
		private:
			void calcLightLocations();

		private:
		};

	}
}