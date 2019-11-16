#pragma once
#include"GL/glew.h"
#include"../maths/maths.h"
#include<vector>
#include<iostream>
#include<random>

namespace Paradox {
	namespace graphics {

class GBuffer
{
private: 
	GLuint m_GFBO;
	int m_Scrheight, m_Scrwidth;
	
	//GLuint m_QuadVAO, m_QuadVBO;
public:
	GLuint m_GPosition, m_GNormal, m_GAlbedoSpec, m_RbDepth;
	GBuffer(int width, int height);
	void createFrameBuffer();
	void bind();
	void unbind(); 
	void bindTextures();
	static void renderQuad();
	auto getGBuffer() -> GLuint; 

	~GBuffer();
private:
	auto lerp(float a, float b, float f) -> float;
};
} }

