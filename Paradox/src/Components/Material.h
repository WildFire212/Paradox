#pragma once
#include<map>
#include <GL\glew.h>
#include<string>
#include"../graphics/Resource/ValueMap.h"
#include"../graphics/Texture.h"
using namespace Paradox::graphics; 
class Material
{

private: 
	ValueMap* m_ValueMap; 
public:

	Material(Texture diffuseTexture, GLfloat sIntensity, GLfloat shine, Texture normalMap);

	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation, GLuint diffuseTextureLocation) const;
	void addTexture(std::string textureName, const Texture& texture);

	GLfloat getFloat(std::string valueName) const; 
	GLuint getTexture(std::string textureName) const; 
	~Material();	

private:
	std::map <std::string, Texture>  m_TextureMap; 

		
	
	

};

