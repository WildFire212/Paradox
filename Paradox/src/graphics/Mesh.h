#pragma once
#include"Renderable.h"
#include"Resource/MeshResource.h"
#include"MeshLoaders/Model.h"
#include"../maths/maths.h"
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
			struct ColliderData {
				maths::vec3 m_MinExtents; 
				maths::vec3 m_MaxExtents; 
				maths::vec3 m_Center;  
				float m_Radius; 
			}m_ColliderData;
		public: 
			//constr and destr
			Mesh(const char* fileLocation); 
			Mesh(std::vector<GLfloat> vertices, std::vector<GLushort> indices,GLuint vertexCount, GLuint indexCount, std::vector<GLfloat> texCoords,Material* material,bool calculateNormals = true);
			Mesh(std::vector<GLfloat> vertices, std::vector<GLushort> indices,GLuint vertexCount, GLuint indexCount, std::vector<GLfloat> texCoords, Material* material,std::vector<GLfloat> normals,bool calculateNormals);
			~Mesh();
		
			//others 
			auto updateCollider(maths::mat4 transformationMatrix);

			//bools 
			auto isModel() const -> const bool; 
			//getters 
			auto getMeshResource() const -> const MeshResource&; 
			auto getModel() const -> const Model&; 
			auto getMaterial() const -> const Material&; 
			auto getColliderData() const -> const ColliderData&; 

			
		private: 
			auto calculateAverageNormals(std::vector<GLushort> indices, unsigned int numOfIndices, std::vector<GLfloat> vertices,
				 unsigned int numOfVertices,std::vector<GLfloat> normals) -> std::vector<GLfloat>;
				//MeshResource load(std::string fileLocation);
			auto load(std::string fileLocation) -> Model; 
			auto calculateColliderData(std::vector <GLfloat> vertices)->void;
			
	};
	
	
}}