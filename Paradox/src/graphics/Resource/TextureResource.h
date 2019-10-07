#pragma once
#include<GL/glew.h>
class TextureResource
{
private: 
	GLuint m_TextureID;
	int m_Height;
	int m_Width;
	int m_BitDepth;
	unsigned int m_ReferenceCount; 
public:
	TextureResource();
	~TextureResource();
	
	void setTextureID(GLuint texID);
	void setHeight(int height);
	void setWidth(int width);
	void setBitDepth(int bitdepth);


	GLuint getTextureID() const;
	int getHeight();
	int getWidth();
	int getBitDepth();
	
};

