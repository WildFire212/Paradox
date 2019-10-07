#include "TextureResource.h"



TextureResource::TextureResource()
{
}


TextureResource::~TextureResource()
{
}

void TextureResource::setTextureID(GLuint texID)
{
	m_TextureID = texID; 
}

void TextureResource::setHeight(int height)
{
	m_Height = height; 
}

void TextureResource::setWidth(int width)
{
	m_Width = width; 
}

void TextureResource::setBitDepth(int bitdepth)
{
	m_BitDepth = bitdepth; 
}

GLuint TextureResource::getTextureID() const
{
	return m_TextureID; 
}

int TextureResource::getHeight()
{
	return m_Height;
}

int TextureResource::getWidth()
{
	return m_Width;
}

int TextureResource::getBitDepth()
{
	return m_BitDepth;
}
