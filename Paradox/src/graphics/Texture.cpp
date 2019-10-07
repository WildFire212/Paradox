#include "Texture.h"
namespace Paradox {
	namespace graphics {
std::map<std::string, std::shared_ptr<TextureResource>> Texture::m_LoadedTextures; 
		Texture::Texture()
		{
		}
		Texture::Texture(const char* fileLocation)
		{

			m_FileLocation = std::string(fileLocation); 
			auto find = m_LoadedTextures.find(m_FileLocation); 
			if (find != m_LoadedTextures.end())
			{
				m_TextureResource = std::shared_ptr<TextureResource>(find->second);
			}
			else {
				
				m_TextureResource = std::make_shared<TextureResource>(load(fileLocation));
				m_LoadedTextures[m_FileLocation] = m_TextureResource; 
			}
		}

		const TextureResource & Texture::getTextureResource() const
		{
			// TODO: insert return statement here
			return *m_TextureResource; 
		}
		
		TextureResource  Texture::load(const char* fileLocation) {
			int height, width, bitdepth;
			GLuint texID; 
			TextureResource textureResource; 
			GLfloat* texData = stbi_loadf(fileLocation, &width,&height, &bitdepth, 0);
			//if (!texData)
			//{
			//	std::cout << "texture Loading failed" << fileLocation << std::endl;
			//
			//}
			//else {
			//	std::cout << "texture Loaded successfully" << fileLocation << std::endl; 
			//}

#if 0
	for (int i = 0; i < m_Width; i++)
	{
		for (int j = 0; j < m_Width; j++)
		{
	
		unsigned bytePerPixel = m_BitDepth;
		GLfloat* pixelOffset = texData + (i + m_Width * j) * bytePerPixel;
		GLfloat r = pixelOffset[0];
		GLfloat g = pixelOffset[1];
		GLfloat b = pixelOffset[2];
		GLfloat a = m_BitDepth >= 4 ? pixelOffset[3] : 0xff;
		std::cout << "r : " << r  << "g :" << g << " b :" << b <<std::endl;

		}
	}
#endif
	if (!texData)
	{
		std::cout << "failed to get tex data"<<fileLocation << std::endl;
		//throw std::runtime_error("failed to load texture data" + m_FileLocation	); 
		//*this = nullptr; 
		//return; 
	}
	else
		std::cout << "loaded successfully" << fileLocation<<std::endl;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (bitdepth == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, texData);
	}
	else if (bitdepth == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, texData);

	}
	//glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);

	//glGenerateTextureMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	textureResource.setTextureID(texID); 
	textureResource.setHeight(height); 
	textureResource.setWidth(width); 
	textureResource.setBitDepth(bitdepth); 

	return textureResource; 
}
		Texture::~Texture()
		{
			m_TextureResource.reset(); 
			auto search = m_LoadedTextures.find(m_FileLocation); 
			if (search->second.use_count() == 0)
			{
				m_LoadedTextures.erase(m_FileLocation); 
			}
		}	

} }
