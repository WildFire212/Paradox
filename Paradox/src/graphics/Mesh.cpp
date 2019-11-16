#include "Mesh.h"
using namespace std;
using namespace maths;
std::map<std::string, std::shared_ptr<Model>> Paradox::graphics::Mesh::m_LoadedMeshes;
Paradox::graphics::Mesh::Mesh(const char * fileLocation)
{
	m_ColliderData = { vec3(1000,1000,1000),vec3(-1000,-1000,-1000),vec3(-1000,-1000,-1000),-1.f };
	m_isModel = true;
	m_FileLocation = std::string(fileLocation);
	auto find = m_LoadedMeshes.find(m_FileLocation);
	if (find != m_LoadedMeshes.end())
	{
		m_Model = std::shared_ptr<Model>(find->second);
	}
	else {

		m_Model = std::make_shared<Model>(load(fileLocation));
		m_LoadedMeshes[m_FileLocation] = m_Model;
	}
	std::vector<GLfloat> a;
	calculateColliderData(a); 
}

Paradox::graphics::Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLushort> indices, GLuint vertexCount, GLuint indexCount, std::vector<GLfloat> texCoords, Material* material,bool calculateNormals)
{
	m_ColliderData = { vec3(1000,1000,1000),vec3(-1000,-1000,-1000),vec3(-1000,-1000,-1000),-1.f };

	m_isModel = false;
	m_FileLocation = ""; 
	m_MeshResource = std::make_shared<MeshResource>(MeshResource()); 
	m_MeshResource->setVertices(vertices); 
	m_MeshResource->setIndices(indices); 
	m_MeshResource->setVertexCount(vertexCount); 
	m_MeshResource->setIndexCount(indexCount); 
	m_MeshResource->setTexCoords(texCoords); 
	std::vector<GLfloat> normals;
	m_MeshResource->setMaterial(material); 
	for (size_t i = 0; i < vertexCount; i++)
	{
		normals.push_back(0.0f);
	}
	m_MeshResource->setNormals(calculateAverageNormals(indices, indexCount, vertices, vertexCount,normals)); 
	calculateColliderData(vertices);
}

Paradox::graphics::Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLushort> indices, GLuint vertexCount, GLuint indexCount, std::vector<GLfloat> texCoords, Material* material,std::vector<GLfloat> normals,bool calculateNormals)
{
	m_ColliderData = { vec3(1000,1000,1000),vec3(-1000,-1000,-1000),vec3(-1000,-1000,-1000),-1.f };

	m_isModel = false;
	m_FileLocation = ""; 
	m_MeshResource = std::make_shared<MeshResource>(MeshResource());
	m_MeshResource->setVertices(vertices);
	m_MeshResource->setIndices(indices);
	m_MeshResource->setVertexCount(vertexCount);
	m_MeshResource->setIndexCount(indexCount);
	m_MeshResource->setTexCoords(texCoords);
	m_MeshResource->setMaterial(material);
	if (calculateNormals == true)
	{
		//for (size_t i = 0; i < vertexCount; i++)
		//{
		//	normals.push_back(0.0f);
		//}
		normals = calculateAverageNormals(indices, indexCount, vertices, vertexCount, normals);
	}
	
	m_MeshResource->setNormals(normals);
	calculateColliderData(vertices);

}



Paradox::graphics::Mesh::~Mesh()
{
	m_Model.reset();
	auto search = m_LoadedMeshes.find(m_FileLocation);
	if (search->second.use_count() == 0)
	{
		m_LoadedMeshes.erase(m_FileLocation);
	}
}
auto Paradox::graphics::Mesh::updateCollider(maths::mat4 transformationMatrix)
{
		//update COlliers usinng transform matrix
}
const MeshResource & Paradox::graphics::Mesh::getMeshResource() const
{
	// TODO: insert return statement here
	return *m_MeshResource; 
}

const Model& Paradox::graphics::Mesh::getModel() const
{
	// TODO: insert return statement here
	return *m_Model;
}

const bool Paradox::graphics::Mesh::isModel() const
{
	return m_isModel;
}

const Material & Paradox::graphics::Mesh::getMaterial() const
{
	// TODO: insert return statement here
	return m_MeshResource->getMaterial(); 
}

auto Paradox::graphics::Mesh::getColliderData() const -> const ColliderData&
{
	return m_ColliderData; 
}



 std::vector<GLfloat> Paradox::graphics::Mesh::calculateAverageNormals(std::vector<GLushort> indices, unsigned int numOfIndices, std::vector<GLfloat> vertices, unsigned int numOfVertices,std::vector<GLfloat> normals)
 {
	// for (size_t i = 0; i < numOfVertices; i++)
	// {
	//	 normals.push_back(0.0f); 
	// }
	for (size_t i = 0; i < numOfIndices; i += 3)
	{
		 //one face (3 vertices)
		 unsigned int ind0 = indices[i] * 3;    //vertex   1
		 unsigned int ind1 = indices[i + 1] * 3;   //		2
		 unsigned int ind2 = indices[i + 2] * 3;	//		3
														 //x coordinate					//y coordinate									//z coordinate
		 glm::vec3 v1(vertices[ind1] - vertices[ind0], vertices[ind1 + 1] - vertices[ind0 + 1], vertices[ind1 + 2] - vertices[ind0 + 2]); // vector 1 
		 glm::vec3 v2(vertices[ind2] - vertices[ind0], vertices[ind2 + 1] - vertices[ind0 + 1], vertices[ind2 + 2] - vertices[ind0 + 2]); // vector 2
		 glm::vec3 normal = glm::cross(v1, v2); //cross product finds the normal 
		 normal = glm::normalize(normal);
	
		 normals[ind0] += normal.x; normals[ind0 + 1] += normal.y; normals[ind0 + 2] = normal.z;
		 normals[ind1] += normal.x; normals[ind1 + 1] += normal.y; normals[ind1 + 2] += normal.z;
		 normals[ind2] += normal.x; normals[ind2 + 1] += normal.y; normals[ind2 + 2] += normal.z;
	
	}
	 return normals;
 }

 Model Paradox::graphics::Mesh::load(std::string fileLocation)
 {
	 return Model(fileLocation);
 }

 auto Paradox::graphics::Mesh::calculateColliderData(std::vector <GLfloat> vertices)->void
 {
	 if (m_isModel)
	 {
		 //do something if it is model 
		 m_ColliderData.m_MinExtents = m_Model->m_Extents.m_MinExtents;
		 m_ColliderData.m_MaxExtents= m_Model->m_Extents.m_MaxExtents;
		
	 }
	 else if (!m_Model) 
	 {
		 //do something if its a mesh (not model)_ 
		 for (size_t i = 0; i < vertices.size(); i+=3)
		 {
			 auto calcExtents = [=](float x, float y, float z) {
				 if (x > m_ColliderData.m_MaxExtents.x)
				 {
					 m_ColliderData.m_MaxExtents.x = x;
				 }
				 if (y > m_ColliderData.m_MaxExtents.y)
				 {
					 m_ColliderData.m_MaxExtents.y = y;
				 }
				 if (z > m_ColliderData.m_MaxExtents.z)
				 {
					 m_ColliderData.m_MaxExtents.z = z;
				 }
						
				 if (x < m_ColliderData.m_MinExtents.x)
				 {
					 m_ColliderData.m_MinExtents.x = x;
				 }
				 if (y < m_ColliderData.m_MinExtents.y)
				 {
					 m_ColliderData.m_MinExtents.y = y;
				 }
				 if (z < m_ColliderData.m_MinExtents.z)
				 {
					 m_ColliderData.m_MinExtents.z = z;
				 }

			 };
			 calcExtents(vertices[i],vertices[i + 1],vertices[i+ 2]);
		 }
	 }
	 float xhalf = (m_ColliderData.m_MaxExtents.x - m_ColliderData.m_MinExtents.x) / 2.0f;
	 float yhalf = (m_ColliderData.m_MaxExtents.y - m_ColliderData.m_MinExtents.y) / 2.0f;
	 float zhalf = (m_ColliderData.m_MaxExtents.z - m_ColliderData.m_MinExtents.z) / 2.0f;
	 m_ColliderData.m_Center = maths::vec3(m_ColliderData.m_MinExtents.x + xhalf, m_ColliderData.m_MinExtents.y + yhalf, m_ColliderData.m_MinExtents.z + zhalf);
	 if (xhalf > yhalf&& xhalf > zhalf)
	 {
		 m_ColliderData.m_Radius = xhalf;
	 }
	 else if (yhalf > xhalf&& yhalf > zhalf)
	 {
		 m_ColliderData.m_Radius = yhalf;
	 }
	 else if (zhalf > xhalf&& zhalf > yhalf)
	 {
		 m_ColliderData.m_Radius = zhalf;
	 }
 }



