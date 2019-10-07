#include"ElementBuffer.h"

namespace Paradox {
	namespace graphics {
		ElementBuffer::ElementBuffer(GLushort* data, GLsizei count) : m_Count(count)
		{
			glGenBuffers(1, &m_BufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		ElementBuffer::ElementBuffer()
		{
			glGenBuffers(1, &m_BufferID);
		}


		void ElementBuffer::bufferData(GLushort * data, GLsizei count, GLenum drawType)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, drawType);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void ElementBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}
		void ElementBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		}

		GLuint ElementBuffer::getCount() const {
			return m_Count;
		}
} }