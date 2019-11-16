#include "AnimatedModel.h"

namespace Paradox {
	namespace graphics {




		AnimatedModel::AnimatedModel(std::string fileLocation)
		{
			load(fileLocation);
			Texture texture("Textures/plain.jpg");
			Material* material = new Material(texture, 0.1f, 0.1f, texture);
			m_MeshResource->setMaterial(material); 
		}

		AnimatedModel::~AnimatedModel()
		{
		}

		void Paradox::graphics::AnimatedModel::load(std::string fileName)
		{

			m_Scene = m_Importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs );


			if (!m_Scene )
			{
				printf("cannot open file %s", fileName);
				if(!m_Scene->HasAnimations())
				printf("Imported models doesn't contain any animation %s", fileName);
			}

			//inverse global transform 
			m_GlobalInverseTransform = m_Scene->mRootNode->mTransformation; 
			m_GlobalInverseTransform.Inverse(); 
			loadNode(m_Scene->mRootNode, m_Scene);

			//load Materials
			
			
			
			std::cout << "successfluuly loaded" << std::endl; 
		}

		void AnimatedModel::loadNode(aiNode * node, const aiScene * scene)
		{

			for (size_t i = 0; i < node->mNumMeshes; i++)
			{
				loadMesh(scene->mMeshes[node->mMeshes[i]], m_Scene);
			}

			for (size_t i = 0; i < node->mNumChildren; i++)
			{
				loadNode(node->mChildren[i], scene);
			}

		}

		void AnimatedModel::loadMesh(aiMesh * mesh, const aiScene * scene)
		{
			//per vertex data
			std::vector<GLfloat> vertices;
			std::vector<GLfloat> texCoords;
			std::vector<GLushort> indices;
			std::vector<GLfloat> normals;

			BoneData test = {0.0f};
			test.boneID =0; 
			glm::vec<4, BoneData> data (test); 
			m_BoneData = std::vector < glm::vec < 4, BoneData>> (mesh->mNumVertices, data);


			for (size_t i = 0; i < mesh->mNumVertices; i++) {
				vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
				if (mesh->mTextureCoords[0]) {
					texCoords.insert(texCoords.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
				}
				else {
					texCoords.insert(texCoords.end(), { 0.0f,0.0f });
				}
				normals.insert(normals.end(), { -mesh->mNormals[i].x,-mesh->mNormals[i].y ,-mesh->mNormals[i].z });
			}

			for (size_t i = 0; i < mesh->mNumFaces; i++) {

				aiFace face = mesh->mFaces[i];
				for (size_t j = 0; j < face.mNumIndices; j++)
				{
					indices.push_back(face.mIndices[j]);
				}

			}

			m_MeshResource = new MeshResource(vertices, indices, texCoords, normals, nullptr);
				
				for (size_t i = 0; i < mesh->mNumBones; i++)
				{

					m_BoneMap[std::string(mesh->mBones[i]->mName.C_Str())] = i;

					for (size_t j = 0; j < mesh->mBones[i]->mNumWeights; j++)
					{

						BoneData mboneData = { 0.0f  };
						mboneData.boneID = 0; 
						mboneData.weight =(float)mesh->mBones[i]->mWeights[j].mWeight;
						mboneData.boneID = i;
						int index = mesh->mBones[i]->mWeights[j].mVertexId;
						
						if (m_BoneData[index].x.weight == 0.0f)
						{
							m_BoneData[index].x.boneID = mboneData.boneID;
							m_BoneData[index].x.weight =  mboneData.weight ;

							

						}
						else if (m_BoneData[index].y.weight ==0.0f)
						{
							m_BoneData[index].y.boneID = mboneData.boneID;
							m_BoneData[index].y.weight = mboneData.weight;

						}
						else if (m_BoneData[index].z.weight == 0.0f)
						{
							m_BoneData[index].z.boneID = mboneData.boneID;
							m_BoneData[index].z.weight = mboneData.weight;

						}
						else if (m_BoneData[index].w.weight == 0.0f)
						{
							m_BoneData[index].w.boneID = mboneData.boneID;
							m_BoneData[index].w.weight = mboneData.weight;

						}

					}



				}


				m_Bones =std::vector<Bone*>(m_BoneMap.size());

				for (size_t i = 0; i < mesh->mNumBones; i++)
				{
					
					m_Bones[i] = new Bone(); 
					m_Bones[i]->m_FinalTransformation = maths::mat4::Identity(); 
					m_Bones[i]->m_Name = mesh->mBones[i]->mName.data;
					m_Bones[i]->m_OffsetMatrix =maths::mat4::aIMatrix4x4ToMat4( mesh->mBones[i]->mOffsetMatrix);
					

				}

		}

		std::vector<Bone*> AnimatedModel::getBones() const
		{
			return m_Bones; 
		}

		const aiScene * AnimatedModel::getScene() const
		{
			return m_Scene; 
		}

		maths::mat4 AnimatedModel::getGlobalInverseTransform() const
		{
			return maths::mat4::aIMatrix4x4ToMat4(m_GlobalInverseTransform); 
		}

		const MeshResource & AnimatedModel::getMeshResource() const
		{
			return *m_MeshResource; 
		}

		const std::vector<glm::vec<4, BoneData>> AnimatedModel::getBoneData() const
		{
			return m_BoneData; 
		}

		

}}

