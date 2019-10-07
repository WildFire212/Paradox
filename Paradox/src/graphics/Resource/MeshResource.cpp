#include "MeshResource.h"


namespace Paradox {
	namespace graphics {

MeshResource::MeshResource()
{
}

MeshResource::MeshResource(std::vector<GLfloat> vertices, std::vector<GLushort> indices, std::vector<GLfloat> texCoords, std::vector<GLfloat> normals,Material* material)
{
	m_Vertices = vertices; 
	m_Indices = indices; 
	m_Normals = normals;
	m_TexCoords = texCoords; 
	m_VertexCount = vertices.size(); 
	m_IndexCount = indices.size(); 
	m_Material = material;
}


MeshResource::~MeshResource()
{
}
void MeshResource::setVertices(std::vector<GLfloat> vertices)
{
	m_Vertices = vertices;
}
void MeshResource::setIndices(std::vector<GLushort> indices)
{
	m_Indices = indices; 
}
void MeshResource::setTexCoords(std::vector<GLfloat> texCoords)
{
	m_TexCoords = texCoords; 
}
void MeshResource::setNormals(std::vector<GLfloat> normals)
{
	m_Normals = normals; 
}
void MeshResource::setVertexCount(GLuint vertexCount)
{
	m_VertexCount = vertexCount; 
}
void MeshResource::setIndexCount(GLuint indexCount)
{
	m_IndexCount = indexCount; 
}
void MeshResource::setMaterial(Material* material)
{
	m_Material = material; 
}
std::vector<GLfloat> MeshResource::getVertices() const
{
	return m_Vertices; 
}
std::vector<GLushort> MeshResource::getIndices() const
{
	return m_Indices;
}
std::vector<GLfloat> MeshResource::getTexCoords() const
{
	return m_TexCoords; 
}
std::vector<GLfloat> MeshResource::getNormals() const
{
	return m_Normals; 
}
GLuint MeshResource::getTexCoordCount() const
{
	return m_TexCoords.size();
}

const Material & MeshResource::getMaterial() const
{
	// TODO: insert return statement here
	return *m_Material; 
}

GLuint MeshResource::getVertexCount() const
{
	return m_VertexCount;
}

GLuint MeshResource::getIndexCount() const
{
	return m_IndexCount;
}

} }
