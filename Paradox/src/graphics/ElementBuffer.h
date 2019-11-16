#pragma once
#include<GL/glew.h>
namespace Paradox {
	namespace graphics {
		class ElementBuffer {
					private:
						GLuint m_BufferID;
						GLuint m_Count;
					public:
						ElementBuffer(GLushort* data, GLsizei count);
						ElementBuffer(); 

						void bufferData(GLushort* data, GLsizei count, GLenum drawType);
						void bind() const;
						void unbind() const;

						auto getCount() const -> GLuint;
						
					};
				
} }