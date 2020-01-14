#pragma once
#ifndef FORWARD_RENDERER_H
#define FORWARD_RENDERER_H
#include"../Shaders/Shader.h"
#include"../graphics/VertexArray.h"
#include"../graphics/Buffer.h"
#include"../graphics/ElementBuffer.h"
#include"../maths/maths.h"

namespace Paradox {
	namespace graphics {

		class ForwardRenderer 
		{
		protected:
			VertexArray* m_VAO;
			Buffer* m_VBO;
			ElementBuffer* m_IBO;
			Shader* m_Shader;

		protected:
		
			ForwardRenderer(Shader* shader) {
				m_Shader = shader;
				m_VAO = new VertexArray();
				m_VBO = new Buffer();
				m_IBO = new ElementBuffer();
			}
		public :
			virtual ~ForwardRenderer() = 0 {}		
			
			auto getShader() const -> const Shader& {
				return *m_Shader;
			}
			
			void setShader(Shader* shader) {
				m_Shader = shader;
			}
		
			virtual auto render(const RenderingEngine& renderingEngine) ->void {}
			


		};
	}
};
#endif