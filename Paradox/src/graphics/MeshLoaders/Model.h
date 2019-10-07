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
	private: 
		std::vector<MeshResource*> m_MeshResourceList; 
		std::vector<unsigned int> m_MeshToTex; 
		std::vector<Material*> m_MaterialList; 
	public:
		Model();
		Model(std::string fileLocation);
		~Model();	
		std::vector<MeshResource*> getMeshResourceList() const; 
	private: 
		void load(std::string fileLocation);

		void loadNode(aiNode* node, const aiScene* scene);
		void loadMeshes(aiMesh* mesh, const aiScene* scene);
		void loadMaterials(const aiScene* scene);
	};

	} }
