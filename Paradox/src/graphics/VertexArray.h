#pragma once
#include<vector>
#include"Buffer.h"
#include<GL/glew.h>


namespace Paradox {
	namespace graphics {
		class VertexArray {
		private: 
			GLuint m_ArrayID; 
			std::vector<Buffer*> m_Buffers; 

		public: 
			VertexArray(); 
			~VertexArray(); 

			void addBuffer(Buffer* buffer, GLuint index); 
			void bind() const; 
			void unbind() const; 
		};
} }  