#pragma once
#include"../graphics/Renderable.h"
#include"../graphics/VertexArray.h"
#include"../graphics/Buffer.h"
#include"../graphics/ElementBuffer.h"
#include"../maths/maths.h"
#include"Component.h"
using namespace Paradox::component;
namespace Paradox {
	namespace graphics {

		class Renderer : public Component {
		protected: 
			VertexArray* m_VAO;
			Buffer* m_VBO; 
			ElementBuffer* m_IBO;
			Shader* m_Shader;
			
		protected: 
			Renderer() {
				m_VAO = new VertexArray();
				m_VBO = new Buffer();
				m_IBO = new ElementBuffer();
				m_Shader = new Shader("src/Shaders/GLSLShaders/GBufferShader.vert", "src/Shaders/GLSLShaders/GBufferShader.frag");
				
				
			}
			Renderer(Shader* shader) {
				m_Shader = shader; 
				m_VAO = new VertexArray();
				m_VBO = new Buffer();
				m_IBO = new ElementBuffer();

			}
			const Shader& getShader() const {
				return *m_Shader;
			}
			void setShader(Shader* shader) {
				m_Shader = shader;
			}

			void render(const RenderingEngine& renderEngine)  override {}
			//virtual void begin() =0 ; 
			//virtual void submit(const Renderable& renderable)= 0; cannot because of 
			//virtual void flush() =0 ; 
			
		};
	}
};
