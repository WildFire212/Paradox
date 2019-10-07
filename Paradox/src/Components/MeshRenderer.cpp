#include "MeshRenderer.h"
#include"../utils/fileutils.h"
#include"../core/GameObject.h"
namespace Paradox {
	namespace graphics {

	
	MeshRenderer::MeshRenderer(Mesh* mesh)://Material* material
		m_Mesh(mesh)
		//m_Material(material)
	
	{
		//if (m_Material == nullptr)
		//{
		//	//to do for nulptr
		//}
		init(); 
		
		
	}

	MeshRenderer::MeshRenderer(Mesh * mesh, Shader * shader) : Renderer(shader),//Material* material
		m_Mesh(mesh)
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
		begin(); 
		submit(meshResource);
		end(); 
	
		flush(meshResource);
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
		m_VAO->bind();
		m_VBO->bind();
		m_VBO->bufferData(NULL, 6000000 , GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_NORMAL_INDEX); 
		glEnableVertexAttribArray(SHADER_COLOR_INDEX); 
		
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE,8* sizeof(GLfloat), (const GLvoid*)0);
		glVertexAttribPointer(SHADER_COLOR_INDEX,2, GL_FLOAT, GL_FALSE,8* sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE,8 * sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));
		
		
		
		m_VBO->unbind();
		
		
		m_VAO->unbind();
	}

	void MeshRenderer::begin() 
	{

		m_VBO->bind(); 
		m_BufferMap = (MeshData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY); 
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

		for (int i = 0; i < meshResource.getVertexCount()/3 ; i ++)
		{
			m_BufferMap->m_Position =  maths::vec3(vertices[i *3],  vertices[i * 3 + 1], vertices[i * 3 + 2]);
			m_BufferMap->m_TexCoords = maths::vec2(texCoords[i * 2],texCoords[i * 2 + 1]);
			m_BufferMap->m_Normals =   maths::vec3(normals[i * 3],  normals[i * 3 + 1], normals[i * 3 + 2]);
			
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
