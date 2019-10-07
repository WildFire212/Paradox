#pragma once
#include"Light.h"
#include<GL/glew.h>
namespace Paradox {
	namespace component
	{

class PointLight : public Light 
{
public:
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,GLfloat dIntensity,glm::vec3 pos,GLfloat con , GLfloat lin , GLfloat exp);
	void UseLight(GLuint aColorLocation, GLuint aIntensityLocation, GLuint dIntensityLocation, GLuint positionLocation,
					GLuint expLocation , GLuint linLocation , GLuint consLocation);
	void renderLight(RenderingEngine& renderingEngine) override;
	~PointLight();
	glm::vec3 position;
	GLfloat linear, constant, exponent;
private: 
};
} }

