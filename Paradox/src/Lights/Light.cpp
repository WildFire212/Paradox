#include "Light.h"
#include"../core/RenderingEngine.h"

namespace Paradox {
	namespace component {
Light::Light()
{

	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	m_ValueMap = new ValueMap();
}
Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
{
	m_ValueMap = new ValueMap(); 
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;

	
}


void Paradox::component::Light::addToEngine(CoreEngine & engine)
{
	engine.getRenderingEngine().addLight(this); 
}

Shader& Light::getShader() const
{
	// TODO: insert return statement here
	return *m_Shader; 
}

void Light::setShader(Shader* shader)
{
	m_Shader = shader;
}

ValueMap * Light::getValueMap() const
{
	return m_ValueMap;
}

Light::~Light()
{
	
}
	}}
