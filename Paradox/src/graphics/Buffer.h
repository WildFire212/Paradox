#pragma once

#include<GL/glew.h>

namespace Paradox {
	namespace graphics {

	class Buffer {
		private: 
			GLuint m_BufferID;
			GLuint m_ComponentCount; 
		public: 
			Buffer(); 
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			void bufferData(GLfloat* data, GLsizei count,GLenum drawType);
			void bind() const; 
			void unbind() const; 
			
			GLuint getComponentCount() const; 
		};
} }