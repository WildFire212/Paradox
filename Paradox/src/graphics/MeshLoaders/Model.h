#pragma once
#include<vector>
#include"../Resource/MeshResource.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>		
#include"../../maths/maths.h"

#include"../Texture.h"
	namespace Paradox {
		namespace graphics {

	class Model
	{
	public : 
		struct Extents {
			maths::vec3 m_MinExtents; 
			maths::vec3 m_MaxExtents; 

		}m_Extents;
	private: 
		std::vector<MeshResource*> m_MeshResourceList; 
		std::vector<unsigned int> m_MeshToTex; 
		std::vector<Material*> m_MaterialList; 
	public:
		Model();
		Model(std::string fileLocation);
		~Model();	
		auto getMeshResourceList() const -> std::vector<MeshResource*>; 
	private: 
		void load(std::string fileLocation);

		void loadNode(aiNode* node, const aiScene* scene);
		void loadMeshes(aiMesh* mesh, const aiScene* scene);
		void loadMaterials(const aiScene* scene);
	};

	} }
