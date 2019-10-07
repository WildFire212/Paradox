#pragma once
//#define STB_IMAGE_IMPLEMENTATION
#include"../../stb_image.h"
#include<GL/glew.h>
#include<map>
#include<iostream>
#include<string>
#include"Resource/TextureResource.h"
#include<memory>
namespace Paradox {
	namespace graphics {

class Texture
{
private: 
	static std::map<std::string, std::shared_ptr<TextureResource>> m_LoadedTextures; 
	std::shared_ptr<TextureResource> m_TextureResource; 
	std::string  m_FileLocation; 
	
public:
	Texture(); 
	Texture(const char* fileLocation);
	const TextureResource& getTextureResource() const; 
	~Texture();
	

private: 
	TextureResource load(const char* fileLocation);
	
};

} }
