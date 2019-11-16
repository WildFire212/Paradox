#pragma once
#include<GL/glew.h>
#include"../maths/maths.h"
#include"../Shaders/Shader.h"
#include"../Components/Component.h"
#include"../graphics/Resource/ValueMap.h"
using namespace Paradox::graphics; 
namespace Paradox {
	namespace component {

class Light : public Component
{
protected : 
	Shader* m_Shader; 
	ValueMap* m_ValueMap; 
public:
	Light();
	Light(GLfloat red , GLfloat green , GLfloat blue , GLfloat aIntensity,GLfloat dIntensity);
	//virtual void UseLight() = 0;
	virtual void renderLight(RenderingEngine& renderingEngine) {};
	//void render(RenderingEngine& engine) override {}
	void addToEngine(CoreEngine& engine) override;
	auto getShader() const -> Shader&;
	void setShader(Shader* shader); 
	auto getValueMap() const -> ValueMap*; 
	~Light();
protected :
	glm::vec3 color;
	GLfloat diffuseIntensity; 
	GLfloat ambientIntensity;


};
} }

