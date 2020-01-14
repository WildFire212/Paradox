#include "Skybox.h"
#include"glm.hpp"
#include"../core/RenderingEngine.h"
namespace Paradox {
	namespace graphics {

		 Skybox* Skybox::getInstance(std::vector<std::string> faceLocations)
		{
			static Skybox* skybox = new Skybox(faceLocations);
			return skybox;
		}

		void Skybox::render(const RenderingEngine& renderEngine)
		{
			//depth mask 
			glDepthFunc(GL_LEQUAL);
			//glDepthRange(1, 1);
			//shader bind 
			m_Shader->bind(); 
			//glDepthRange(1, 1);
			//render mesh
			m_Shader->SetUniform1i("skybox", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyboxCubeMap->getCubeMap());
			//m_Shader->updateAllUniforms(nullptr, &renderEngine, nullptr);
			glm::mat4 proj = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);
			m_Shader->SEtmat4("T_projection", proj);
			m_Shader->SEtmat4("T_view", glm::mat4(glm::mat3(renderEngine.getMainCamera().calculateViewMatrixGLM())));
		
			renderSkyMesh(); 
			
			//unbind shader maybe
			m_Shader->unbind(); 
			//glDepthRange(0, 1);
			glDepthFunc(GL_LESS);
		}

		 Skybox::Skybox(std::vector<std::string> faceLocations) : ForwardRenderer(new Shader("src/Shaders/GLSLShaders/GBufferSkyboxShader.vert",
																					  "src/Shaders/GLSLShaders/GBufferSkyboxShader.frag"))
		 {	
			 //setting up the mesh 

			 

			 
			 //cube map setup
			 m_SkyboxCubeMap = new CubeMap(faceLocations);


			 // Mesh Setup
			 std::vector<GLushort> skyboxIndices= {
				 // front
				 0, 1, 2,
				 2, 1, 3,
				 // right
				 2, 3, 5,
				 5, 3, 7,
				 // back
				 5, 7, 4,
				 4, 7, 6,
				 // left
				 4, 6, 0,
				 0, 6, 1,
				 // top
				 4, 0, 5,
				 5, 0, 2,
				 // bottom
				 1, 6, 3,
				 3, 6, 7
			 };

			 std::vector<GLfloat> skyboxVertices = {
				 -1.0f, 1.0f, -1.0f,	
				 -1.0f, -1.0f, -1.0f,	
				 1.0f, 1.0f, -1.0f,		
				 1.0f, -1.0f, -1.0f,	

				 -1.0f, 1.0f, 1.0f,		
				 1.0f, 1.0f, 1.0f,		
				 -1.0f, -1.0f, 1.0f,	
				 1.0f, -1.0f, 1.0f		
			 };

			 std::vector<GLfloat> skyboxTexCoords = {
					0.0f, 0.0f,
				 0.0f, 0.0f,
				 0.0f, 0.0f,
					0.0f, 0.0f,
				 0.0f, 0.0f,
				 0.0f, 0.0f,
					0.0f, 0.0f,
				 0.0f, 0.0f,
			 };

			 std::vector<GLfloat> skyboxNormals = {
					0.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f,

				 0.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 0.0f
			 };

		
			 GLfloat vertices[] = {
					 -1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
					 -1.0f, -1.0f, -1.0f,	 0.0f, 0.0f,   	 0.0f, 0.0f, 0.0f,
					 1.0f, 1.0f, -1.0f,		 0.0f, 0.0f,   	 0.0f, 0.0f, 0.0f,
					 1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

					 -1.0f, 1.0f, 1.0f,		 0.0f, 0.0f,   	 0.0f, 0.0f, 0.0f,
					 1.0f, 1.0f, 1.0f,		 0.0f, 0.0f,   	 0.0f, 0.0f, 0.0f,
					 -1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
					 1.0f, -1.0f, 1.0f,			 0.0f, 0.0f,	 0.0f, 0.0f, 0.0f,
			 };

			 Texture texture("Textures/grass.jpg");
			 m_SkyMesh = new Mesh(skyboxVertices, skyboxIndices, 
				 skyboxVertices.size(), skyboxIndices.size(),skyboxTexCoords, 
				 new Material(texture, 0.1f,0.1f, texture) );
			 m_VAO->bind();
			 m_IBO->bind();
			 m_IBO->bufferData(FileUtils::convertToArray(m_SkyMesh->getMeshResource().getIndices()), m_SkyMesh->getMeshResource().getIndexCount(), GL_STATIC_DRAW);
			 m_VBO->bind();
			 m_VBO->bufferData(vertices, 64, GL_STATIC_DRAW);


			 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
			 glEnableVertexAttribArray(0);
			 glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
			 glEnableVertexAttribArray(1);
			 glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
			 glEnableVertexAttribArray(2);

			 m_VBO->unbind();
			 m_IBO->unbind();
			 m_VAO->unbind();
			 
		 }

		 auto Skybox::renderSkyMesh() const -> void
		 {
			 m_VAO->bind();
			 m_IBO->bind();
			 glDrawElements(GL_TRIANGLES, m_SkyMesh->getMeshResource().getIndexCount(), GL_UNSIGNED_SHORT, 0);
			 m_IBO->unbind();
			 m_VAO->unbind();
		 }


	}
}