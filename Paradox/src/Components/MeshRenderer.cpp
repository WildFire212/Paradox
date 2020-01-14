#include "MeshRenderer.h"
#include"../utils/fileutils.h"
#include"../core/GameObject.h"
namespace Paradox {
	namespace graphics {

	
	MeshRenderer::MeshRenderer(Mesh* mesh,bool isBatchRendering)://Material* material
		m_Mesh(mesh),
		m_IsBatchRendering(isBatchRendering)
		//m_Material(material)
	
	{
		//if (m_Material == nullptr)
		//{
		//	//to do for nulptr
		//}
		init(); 
		
		
	}

	MeshRenderer::MeshRenderer(Mesh * mesh, Shader * shader, bool isBatchRendering) : Renderer(shader),//Material* material
		m_Mesh(mesh),
		m_IsBatchRendering(isBatchRendering)
		//m_Material(material)
	{
		//if (m_Material == nullptr)
		//{
		//	//to do for nulptr
		//}
		init();
		
	}

	void MeshRenderer::renderMesh(const MeshResource & meshResource) 
	{
		if(m_IsBatchRendering)
		{ 
		begin(); 
		submit(meshResource);
		end(); 
		flush(meshResource);
	
		}
		else if (!m_IsBatchRendering)
		{
			flush(meshResource); 
		}
	}

	void MeshRenderer::render(const RenderingEngine & renderingEngine) 
	{
		
		m_Shader->bind();
		//for every mesh 
		if (m_Mesh->isModel() == false)
		{
			m_Shader->updateAllUniforms(this->m_Parent->getTransform(), &renderingEngine, &m_Mesh->getMaterial()); //mesh->getMaterial; 
			
			renderMesh(m_Mesh->getMeshResource());
			
			


		}
		else {
			for (size_t i = 0; i < m_Mesh->getModel().getMeshResourceList().size(); i++)
			{
			m_Shader->updateAllUniforms(this->m_Parent->getTransform(), &renderingEngine, &m_Mesh->getModel().getMeshResourceList()[i]->getMaterial()); //mesh->getMaterial; 
			renderMesh(*m_Mesh->getModel().getMeshResourceList()[i]);

			}
			
		}
		//end loop 
		m_Shader->unbind();
		

	}

	void MeshRenderer::setBatchRendering(bool isBatchRendering)
	{
		m_IsBatchRendering = isBatchRendering; 
	}



	void MeshRenderer::init()
	{
		if (m_IsBatchRendering)
		{
			m_VAO->bind();
			m_VBO->bind();
			m_VBO->bufferData(NULL, 6000000, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_NORMAL_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glEnableVertexAttribArray(SHADER_TANGENT_INDEX);
			glEnableVertexAttribArray(SHADER_BITANGENT_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (const GLvoid*)0);
			glVertexAttribPointer(SHADER_COLOR_INDEX, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
			glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));
			glVertexAttribPointer(SHADER_TANGENT_INDEX, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (const GLvoid*)(8 * sizeof(GLfloat)));
			glVertexAttribPointer(SHADER_BITANGENT_INDEX, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (const GLvoid*)(11 * sizeof(GLfloat)));
			m_VBO->unbind();
			m_VAO->unbind();
		}
		else if (!m_IsBatchRendering)
		{
			if (!m_Mesh->isModel())
			{
				const int stride = 14; 
				const int count = stride * (m_Mesh->getMeshResource().getVertexCount() / 3);
				GLfloat* vertices = new GLfloat[count];

				//writing vertices into array 
				for (int i = 0; i < m_Mesh->getMeshResource().getVertexCount(); i += 3)
				{
					int i0 = i;
					int i1 = i + 1;
					int i2 = i + 2;
					i0 /= 3;
					i1 /= 3;
					i2 /= 3;
					i0 = i0 * stride;
					i1 = i1 * stride + 1;
					i2 = i2 * stride + 2;
					vertices[i0] = m_Mesh->getMeshResource().getVertices()[i];
					vertices[i1] = m_Mesh->getMeshResource().getVertices()[i + 1];
					vertices[i2] = m_Mesh->getMeshResource().getVertices()[i + 2];
				}
				//for writing texture coords 
				for (int i = 0; i < m_Mesh->getMeshResource().getTexCoordCount(); i += 2)
				{
					int i0 = i;
					int i1 = i + 1;
					i0 /= 2;
					i1 /= 2;
					i0 = i0 * stride + 3;
					i1 = i1 * stride + 4;
					vertices[i0] = m_Mesh->getMeshResource().getTexCoords()[i];
					vertices[i1] = m_Mesh->getMeshResource().getTexCoords()[i + 1];
				}
				//for writing normals in the array 
				for (int i = 0; i < m_Mesh->getMeshResource().getVertexCount(); i += 3)
				{
					int i0 = i;
					int i1 = i + 1;
					int i2 = i + 2;
					i0 /= 3;
					i1 /= 3;
					i2 /= 3;
					i0 = i0 * stride + 5;
					i1 = i1 * stride + 6;
					i2 = i2 * stride + 7;
					vertices[i0] = m_Mesh->getMeshResource().getNormals()[i];
					vertices[i1] = m_Mesh->getMeshResource().getNormals()[i + 1];
					vertices[i2] = m_Mesh->getMeshResource().getNormals()[i + 2];
				}

				//for writing tangents and bitangents 
				for (int i = 0; i < m_Mesh->getMeshResource().getVertexCount(); i += 3)
				{
					int index = (i / 3) * stride; 

					vertices[index + 8 ] = m_Mesh->getMeshResource().getTangents()[i];
					vertices[index + 9 ] = m_Mesh->getMeshResource().getTangents()[i + 1];
					vertices[index + 10] = m_Mesh->getMeshResource().getTangents()[i + 2];
					vertices[index + 11] = m_Mesh->getMeshResource().getBitangents()[i ];
					vertices[index + 12] = m_Mesh->getMeshResource().getBitangents()[i + 1];
					vertices[index + 13] = m_Mesh->getMeshResource().getBitangents()[i + 2];
				}
				m_VAO->bind();
				m_IBO->bind();
				m_IBO->bufferData(FileUtils::convertToArray(m_Mesh->getMeshResource().getIndices()), m_Mesh->getMeshResource().getIndexCount(), GL_STATIC_DRAW);
				m_VBO->bind();
				m_VBO->bufferData(vertices, count, GL_STATIC_DRAW);


				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, 0);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, (void*)(sizeof(vertices[0]) * 3));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, (void*)(sizeof(vertices[0]) * 5));
				glEnableVertexAttribArray(2);

				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, (void*)(sizeof(vertices[0]) * 8));
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, (void*)(sizeof(vertices[0]) * 11));
				glEnableVertexAttribArray(4);

				m_VBO->unbind();
				m_IBO->unbind();
				m_VAO->unbind();
			}
			else if (m_Mesh->isModel())
			{
				const int stride = 14;
				for (size_t j = 0; j< m_Mesh->getModel().getMeshResourceList().size(); j++)
				{
					
						const int count = stride * (m_Mesh->getModel().getMeshResourceList()[j]->getVertexCount()/ 3);
						GLfloat* vertices = new GLfloat[count];

						//writing vertices into array 
						for (int i = 0; i < m_Mesh->getModel().getMeshResourceList()[j]->getVertexCount(); i += 3)
						{
							int i0 = i;
							int i1 = i + 1;
							int i2 = i + 2;
							i0 /= 3;
							i1 /= 3;
							i2 /= 3;
							i0 = i0 * stride;
							i1 = i1 * stride + 1;
							i2 = i2 * stride + 2;
							vertices[i0] = m_Mesh->getModel().getMeshResourceList()[j]->getVertices()[i];
							vertices[i1] = m_Mesh->getModel().getMeshResourceList()[j]->getVertices()[i + 1];
							vertices[i2] = m_Mesh->getModel().getMeshResourceList()[j]->getVertices()[i + 2];
						}
						//for writing texture coords 
						for (int i = 0; i < m_Mesh->getModel().getMeshResourceList()[j]->getTexCoordCount(); i += 2)
						{
							int i0 = i;
							int i1 = i + 1;
							i0 /= 2;
							i1 /= 2;
							i0 = i0 * stride + 3;
							i1 = i1 * stride + 4;
							vertices[i0] = m_Mesh->getModel().getMeshResourceList()[j]->getTexCoords()[i];
							vertices[i1] = m_Mesh->getModel().getMeshResourceList()[j]->getTexCoords()[i + 1];
						}
						//for writing normals in the array 
						for (int i = 0; i < m_Mesh->getModel().getMeshResourceList()[j]->getVertexCount(); i += 3)
						{
							int i0 = i;
							int i1 = i + 1;
							int i2 = i + 2;
							i0 /= 3;
							i1 /= 3;
							i2 /= 3;
							i0 = i0 *stride + 5;
							i1 = i1 *stride + 6;
							i2 = i2 *stride + 7;
							vertices[i0] = m_Mesh->getModel().getMeshResourceList()[j]->getNormals()[i];
							vertices[i1] = m_Mesh->getModel().getMeshResourceList()[j]->getNormals()[i + 1];
							vertices[i2] = m_Mesh->getModel().getMeshResourceList()[j]->getNormals()[i + 2];
						}

						for (int i = 0; i < m_Mesh->getModel().getMeshResourceList()[j]->getVertexCount(); i += 3)
						{
							int index = (i / 3) * stride;

							vertices[index + 8] = m_Mesh->getModel().getMeshResourceList()[j]->getTangents()[i];
							vertices[index + 9] = m_Mesh->getModel().getMeshResourceList()[j]->getTangents()[i + 1];
							vertices[index + 10] = m_Mesh->getModel().getMeshResourceList()[j]->getTangents()[i + 2];
							vertices[index + 11] = m_Mesh->getModel().getMeshResourceList()[j]->getBitangents()[i];
							vertices[index + 12] = m_Mesh->getModel().getMeshResourceList()[j]->getBitangents()[i + 1];
							vertices[index + 13] = m_Mesh->getModel().getMeshResourceList()[j]->getBitangents()[i + 2];
						}

						m_VAO->bind();
						m_IBO->bind();
						m_IBO->bufferData(FileUtils::convertToArray(m_Mesh->getModel().getMeshResourceList()[j]->getIndices()), m_Mesh->getModel().getMeshResourceList()[j]->getIndexCount(), GL_STATIC_DRAW);
						m_VBO->bind();
						m_VBO->bufferData(vertices, count, GL_STATIC_DRAW);



						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, 0);
						glEnableVertexAttribArray(0);
						glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, (void*)(sizeof(vertices[0]) * 3));
						glEnableVertexAttribArray(1);
						glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, (void*)(sizeof(vertices[0]) * 5));
						glEnableVertexAttribArray(2);

						glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, (void*)(sizeof(vertices[0]) * 8));
						glEnableVertexAttribArray(3);
						glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 14, (void*)(sizeof(vertices[0]) * 11));
						glEnableVertexAttribArray(4);


						m_VBO->unbind();
						m_IBO->unbind();
						m_VAO->unbind();
				}
			}
		}
		
	}

	void MeshRenderer::begin() 
	{

		m_VBO->bind(); 
		m_BufferMap =  (MeshData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY); 
	}

	void MeshRenderer::submit(const MeshResource& meshResource)
	{

		m_VAO->bind();
		//FileUtils::convertToArray(meshResource.getIndices())
		m_IBO->bufferData(meshResource.getIndices().data(), meshResource.getIndexCount(), GL_DYNAMIC_DRAW); //new ElementBuffer(&meshResource.getIndices()[0], meshResource.getIndexCount());//cannot create object every time 	

		m_VAO->unbind();
		std::vector<GLfloat> vertices = meshResource.getVertices();		//main Problem file utils 
		std::vector<GLfloat> normals= meshResource.getNormals(); 
		std::vector<GLfloat> texCoords = meshResource.getTexCoords(); 
		std::vector<GLfloat> tangents = meshResource.getTangents(); 
		std::vector<GLfloat> bitangents = meshResource.getBitangents(); 
		for (int i = 0; i < meshResource.getVertexCount()/3 ; i ++)
		{
			m_BufferMap->m_Position =  maths::vec3(vertices[i *3],  vertices[i * 3 + 1], vertices[i * 3 + 2]);
			m_BufferMap->m_TexCoords = maths::vec2(texCoords[i * 2],texCoords[i * 2 + 1]);
			m_BufferMap->m_Normals =   maths::vec3(normals[i * 3],  normals[i * 3 + 1], normals[i * 3 + 2]);
			m_BufferMap->m_Tangents =   maths::vec3(tangents[i * 3], tangents[i * 3 + 1], tangents[i * 3 + 2]);
			m_BufferMap->m_Bitangents =   maths::vec3(bitangents[i * 3], bitangents[i * 3 + 1], bitangents[i * 3 + 2]);
			
			m_BufferMap++;
	
		}
		
	}

	void MeshRenderer::flush(const MeshResource& meshResource)
	{
		
		m_VAO->bind();
		m_IBO->bind();
		glDrawElements(GL_TRIANGLES, meshResource.getIndexCount(), GL_UNSIGNED_SHORT, 0);
		m_IBO->unbind();
		m_VAO->unbind();
	}
	
	
	void MeshRenderer::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void MeshRenderer::SetMesh(Mesh * mesh)
	{
		m_Mesh = mesh;
	}

	const Mesh & MeshRenderer::getMesh() const
	{
		return *m_Mesh; 
	}

	MeshRenderer::~MeshRenderer()
	{
	}
} }
