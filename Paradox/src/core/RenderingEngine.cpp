#include "RenderingEngine.h"
#include"../Lights/Light.h"
#include"GameObject.h"

namespace Paradox {
	namespace graphics {
		void calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount,
			unsigned int vLength, unsigned int normalOffset)
		{
			for (size_t i = 0; i < indiceCount; i += 3)
			{
				unsigned int in0 = indices[i] * vLength;
				unsigned int in1 = indices[i + 1] * vLength;
				unsigned int in2 = indices[i + 2] * vLength;
				glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
				glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
				glm::vec3 normal = glm::cross(v1, v2);
				normal = glm::normalize(normal);

				in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
				vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
				vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
				vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
			}

			for (size_t i = 0; i < verticeCount / vLength; i++)
			{
				unsigned int nOffset = i * vLength + normalOffset;
				glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
				vec = glm::normalize(vec);
				vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
			}
		}
		
		void drawMesh() {
			GLuint VAO, VBO, IBO; 
			unsigned int indices[] = {
	0, 3, 1,
	1, 3, 2,
	2, 3, 0,
	0, 1, 2
			};

			GLfloat vertices[] = {
				//	x      y      z			u	  v			nx	  ny    nz
					-1.0f, -1.0f, -0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
					0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
					1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
			};
			calcAverageNormals(indices, 12, vertices, 32, 8, 5);
			int numOfIndices = 12; 
			int numOfVertices = 32; 

			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
			glEnableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glBindVertexArray(0);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		RenderingEngine::RenderingEngine(int height, int width)
		{
			m_GBuffer = new GBuffer(width, height);
			m_ActiveLight = new Light(); 
			m_MainCamera = new Camera(); 
			glClearColor(0.0, 0.0f, 0.0f, 0.0f);
			//glFrontFace(GL_CW);
			//glCullFace(GL_BACK); 
			//glEnable(GL_CULL_FACE); 
			glEnable(GL_DEPTH_TEST); 
		}

		void RenderingEngine::render(GameObject * gameObject)
		{
			//TO DO 

			if (&getMainCamera() == nullptr)
			{
				throw std::runtime_error("there is no camera..");
			}
			m_GBuffer->bind(); 
			glClearColor(0.0, 0.0f,0.0f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
			
			//m_GBufferShader->updateAllUniforms(&transform, this, &material);
			//drawMesh(); 
			gameObject->renderAll(*this); 
			
			m_GBuffer->unbind(); 
			
			glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		//	glClearColor(1.0f,0.0f, 1.0f, 0.0f);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glDepthMask(false);
			//glDepthFunc(GL_EQUAL);
			//

			for (Light* light : m_Lights)
			{
				m_ActiveLight = light; 
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_GBuffer->m_GPosition);	//gbuffer

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_GBuffer->m_GNormal);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D ,m_GBuffer->m_GAlbedoSpec);
				light->renderLight(*this); 
			GBuffer::renderQuad();

			}
			glDepthFunc(GL_LESS);
			glDepthMask(true);
			glDisable(GL_BLEND);
			
			
		}

		void RenderingEngine::addLight(Light * light)
		{
			m_Lights.push_back(light); 
		}

		const Camera & RenderingEngine::getMainCamera() const
		{
			// TODO: insert return statement here
			return *m_MainCamera; 
		}

		void RenderingEngine::setMainCamera(Camera * camera) 
		{
			m_MainCamera = camera; 
		}

		const Light * RenderingEngine::getActiveLight() const
		{
			return m_ActiveLight;
		}


		RenderingEngine::~RenderingEngine()
		{
		}

	}
}