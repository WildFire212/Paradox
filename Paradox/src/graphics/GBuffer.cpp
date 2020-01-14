#include "GBuffer.h"


namespace Paradox {
	namespace graphics {

		GBuffer::GBuffer(int width, int height)
		{
			//m_QuadVAO = 0;
			m_Scrheight = height;
			m_Scrwidth = width;
			createFrameBuffer(); 
		}

		void GBuffer::createFrameBuffer()
		{
			glGenFramebuffers(1, &m_GFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, m_GFBO);
			bindTextures();
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
			else {
				std::cout << "frame buffer initialization failed" << std::endl;
			}
		}

		void GBuffer::bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_GFBO);
		}

		void GBuffer::unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		void GBuffer::bindTextures()
		{
			//Texture for position	sx
			glGenTextures(1, &m_GPosition);
			glBindTexture(GL_TEXTURE_2D, m_GPosition);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Scrwidth, m_Scrheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_GPosition, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

			//Texture for normals
			glGenTextures(1, &m_GNormal);
			glBindTexture(GL_TEXTURE_2D, m_GNormal);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_Scrwidth, m_Scrheight, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_GNormal, 0);
			glBindTexture(GL_TEXTURE_2D, 0);		

			//Texture for albedo
			glGenTextures(1, &m_GAlbedoSpec);
			glBindTexture(GL_TEXTURE_2D, m_GAlbedoSpec);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Scrwidth, m_Scrheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_GAlbedoSpec, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			
			//Texture for NormalMapping
			glGenTextures(1, &m_GNormalMapping);
			glBindTexture(GL_TEXTURE_2D, m_GNormalMapping);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_Scrwidth, m_Scrheight, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_GNormalMapping, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

			//Texture for Tangent
			glGenTextures(1, &m_GTangent);
			glBindTexture(GL_TEXTURE_2D, m_GTangent);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_Scrwidth, m_Scrheight, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, m_GTangent, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

			//Texture for BitTangents
			glGenTextures(1, &m_GBitTangent);
			glBindTexture(GL_TEXTURE_2D, m_GBitTangent);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_Scrwidth, m_Scrheight, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, m_GBitTangent, 0);
			glBindTexture(GL_TEXTURE_2D, 0);

			unsigned int attachments[6] = { GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 ,GL_COLOR_ATTACHMENT2 ,GL_COLOR_ATTACHMENT3,GL_COLOR_ATTACHMENT4,GL_COLOR_ATTACHMENT5 };
			glDrawBuffers(6, attachments);


			glGenRenderbuffers(1, &m_RbDepth);
			glBindRenderbuffer(GL_RENDERBUFFER, m_RbDepth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Scrwidth, m_Scrheight);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RbDepth);

		}
		void GBuffer::renderQuad()
		{
			GLuint m_QuadVAO =0, m_QuadVBO;
			if (m_QuadVAO == 0)
			{
				GLfloat quadVertices[20] = {
					  -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
					-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
					 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
					 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,

				};
				glGenVertexArrays(1, &m_QuadVAO);
				glBindVertexArray(m_QuadVAO);

				glGenBuffers(1, &m_QuadVBO);
				glBindBuffer(GL_ARRAY_BUFFER, m_QuadVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices)  , &quadVertices, GL_STATIC_DRAW);


				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
				glEnableVertexAttribArray(1);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
			}

			glBindVertexArray(m_QuadVAO);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);
			//just add some vertexArray buffers 
		}

		GLuint GBuffer::getGBuffer()
		{
			return m_GFBO;
		}
	
		GBuffer::~GBuffer()
		{
		}

		float GBuffer::lerp(float a, float b, float f)
		{
			return (a + f * (b - a));
		}

}}