#pragma once
#include"Renderable.h"
#include"Resource/MeshResource.h"
#include"MeshLoaders/Model.h"
#include<memory>
namespace Paradox {
	namespace graphics {

		class  Mesh :public Renderable {
		private: 
			static std::map<std::string, std::shared_ptr<Model>> m_LoadedMeshes;
			std::shared_ptr<MeshResource> m_MeshResource;
			std::shared_ptr<Model> m_Model;
			std::string m_FileLocation; 
			bool m_isModel; 

		public: 
		
			Mesh(const char* fileLocation); 
			Mesh(std::vector<GLfloat> vertices, std::vector<GLushort> indices,GLuint vertexCount, GLuint indexCount, std::vector<GLfloat> texCoords,Material* material,bool calculateNormals = true);
			Mesh(std::vector<GLfloat> vertices, std::vector<GLushort> indices,GLuint vertexCount, GLuint indexCount, std::vector<GLfloat> texCoords, Material* material,std::vector<GLfloat> normals,bool calculateNormals);
			
			~Mesh(); 
			const MeshResource& getMeshResource() const; 
			const Model& getModel() const; 
			const bool isModel() const; 

			const Material& getMaterial() const; 
			
		private: 
			std::vector<GLfloat> calculateAverageNormals(std::vector<GLushort> indices, unsigned int numOfIndices, std::vector<GLfloat> vertices,
				 unsigned int numOfVertices,std::vector<GLfloat> normals);
//MeshResource load(std::string fileLocation);
			
			Model load(std::string fileLocation); 
			
	};
	
	
}}