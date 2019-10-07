#include "Model.h"


namespace Paradox {
	namespace graphics {

		Model::Model()
		{
		}
		Model::Model(std::string fileLocation)
		{
			load(fileLocation);

		}
		Model::~Model()
		{
		}

		void Model::load(std::string fileLocation)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(fileLocation, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
			if (!scene) {
				printf("Model (%s) failed to load : %s", fileLocation, importer.GetErrorString());
				return;
			}
			loadNode(scene->mRootNode, scene);
			loadMaterials(scene);

			for (size_t i = 0; i < m_MeshResourceList.size(); i++)
			{
				unsigned int materialIndex = m_MeshToTex[i];
				if (materialIndex < m_MaterialList.size() && m_MaterialList[materialIndex])
				{
					m_MeshResourceList[i]->setMaterial(m_MaterialList[materialIndex]);
				}

				if (!(&m_MeshResourceList[i]->getMaterial()))
				{
					

						Texture* texture = new Texture("Textures/plain.png");
						m_MaterialList[i] = new Material(*texture, 0.3f, 0.3f, *texture);
					
				}
			}

		}

		void Model::loadNode(aiNode * node, const aiScene * scene)
		{
			//load all the node meshes
			for (size_t i = 0; i < node->mNumMeshes; i++) {
				loadMeshes(scene->mMeshes[node->mMeshes[i]], scene);
			}

			for (size_t i = 0; i < node->mNumChildren; i++)	
			{
				loadNode(node->mChildren[i], scene);
			}

		}

		void Model::loadMeshes(aiMesh * mesh, const aiScene * scene)
		{
			std::vector<GLfloat> vertices;
			std::vector<GLfloat> texCoords;
			std::vector<GLushort> indices;
			std::vector<GLfloat> normals;

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

			MeshResource* meshResource = new MeshResource(vertices, indices, texCoords, normals, nullptr);


			m_MeshToTex.push_back(mesh->mMaterialIndex);
			m_MeshResourceList.push_back(meshResource);
		}

		void Model::loadMaterials(const aiScene * scene)
		{

			m_MaterialList.resize(scene->mNumMaterials);
			for (size_t i = 0; i < scene->mNumMaterials; i++) {
				aiMaterial* material = scene->mMaterials[i];		//material scene->mMaterials[i]
				m_MaterialList[i] = nullptr;
				if (material->GetTextureCount(aiTextureType_DIFFUSE))
				{
					aiString path;
					if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {		//Get Texture(aiTextureType_DIFFUSE
						int idx = std::string(path.data).rfind("\\");
						std::string filename = std::string(path.data).substr(idx + 1);
						std::string texPath = std::string("Textures/") + filename;
						Texture *texture = new Texture(texPath.c_str());

						if (texture == nullptr)
						{
							printf("Failed to load texture at: %s\n", texPath);
							delete texture;
						}
						m_MaterialList[i] = new Material(*texture, 0.9f, 0.9f, *texture);


					}
				}
				if(!m_MaterialList[i] ){
				
					Texture* texture = new Texture("Textures/plain.png");
					m_MaterialList[i] = new Material(*texture, 0.3f, 0.3f, *texture);
				}

			}
		}
		std::vector<MeshResource*> Model::getMeshResourceList() const
		{
			// TODO: insert return statement here
			return m_MeshResourceList;
		}
	}
}