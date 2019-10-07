#pragma once
#include<assert.h>
#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>
#include<assimp/scene.h>
#include<string>
#include<vector>
#include<GL/glew.h>
#include"../../../maths/maths.h"
#include<map>
#include"Bone.h"
#include<iostream>
#include"../../Resource/MeshResource.h"
namespace Paradox {
	namespace graphics{
	struct BoneData{
		float weight; 
		int boneID ;
	};
	class AnimatedModel{
	
	const aiScene* m_Scene; 
	
	Assimp::Importer m_Importer; 
	aiMatrix4x4 m_GlobalInverseTransform; 

	//per vertex data
	MeshResource* m_MeshResource; 
	

	std::vector<glm::vec<4, BoneData>> m_BoneData;

	//bone name and index map
	std::map<std::string, int > m_BoneMap;


	//boneData 
	std::vector<Bone*> m_Bones; 
public:
	AnimatedModel(std::string fileLocation);
	~AnimatedModel();
	void load(std::string fileName); 
	void loadNode(aiNode* node, const aiScene* scene);
	void loadMesh(aiMesh* mesh, const aiScene* scene);
	//void loadMaterials(const aiScene* scene); 
	

	//getter and setter 
	std::vector<Bone*> getBones() const; 
	const aiScene* getScene() const; 
	maths::mat4 getGlobalInverseTransform() const; 
	const MeshResource& getMeshResource() const; 
	const std::vector<glm::vec<4, BoneData>> getBoneData() const; 
	
};

} }
