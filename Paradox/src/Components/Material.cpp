#include "Material.h"

Material::Material(Texture diffuseTexture, GLfloat sIntensity, GLfloat shine, Texture normalMap)
{
	m_ValueMap = new ValueMap(); 
	addTexture("diffuseTexture",diffuseTexture); 
	addTexture("normalMap" , diffuseTexture); 
	m_ValueMap->addFloat("specularIntensity", sIntensity); 
	m_ValueMap->addFloat("shininess", shine);


}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation,GLuint diffuseTextureLocation) const
{
	//diffuse Texture set to unioform sampler 1
	glUniform1i(diffuseTextureLocation, 1); 
	glActiveTexture(GL_TEXTURE1);	
//	glBindTexture(GL_TEXTURE_2D, getTexture("diffuseTexture").getTextureResource().getTextureID()); 
	
	
	glUniform1f(specularIntensityLocation, getFloat("specularIntensity"));
	glUniform1f(shininessLocation, getFloat("shininess"));

}

void Material::addTexture(std::string textureName, const Texture & texture)
{
	m_TextureMap[textureName] = texture; 
}

GLfloat Material::getFloat(std::string valueName) const
{
	return m_ValueMap->getFloat(valueName); 
}

GLuint Material::getTexture(std::string textureName) const 
{
	auto search = m_TextureMap.find(textureName);
	if (search != m_TextureMap.end()) {
		return search->second.getTextureResource().getTextureID();
	}
	else {
		return 0;
	}

}

Material::~Material()
{
}
