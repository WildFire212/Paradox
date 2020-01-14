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
	calculateTangentSpace(); 
}

MeshResource::MeshResource(std::vector<GLfloat> vertices, std::vector<GLushort> indices, std::vector<GLfloat> texCoords, std::vector<GLfloat> normals, Material* material, std::vector<GLfloat> tangents, std::vector<GLfloat> bitangents)
{
	
	m_Vertices = vertices;
	m_Indices = indices;
	m_Normals = normals;
	m_TexCoords = texCoords;
	m_VertexCount = vertices.size();
	m_IndexCount = indices.size();
	m_Material = material;
	m_Tangents = tangents; 
	m_Bitangents = bitangents; 
}


MeshResource::~MeshResource()
{
}

void MeshResource::calculateTangentSpace()
{
	using namespace maths;
	m_Tangents = std::vector<GLfloat>(m_VertexCount, 0);
	m_Bitangents = std::vector<GLfloat>(m_VertexCount, 0);

	for (size_t i = 0; i < m_Indices.size(); i += 3)
	{
		vec3 pos0 = maths::vec3(m_Vertices[m_Indices[i] * 3], m_Vertices[m_Indices[i] * 3 + 1], m_Vertices[m_Indices[i] * 3 + 2]);
		vec3 pos1 = maths::vec3(m_Vertices[m_Indices[i + 1] * 3], m_Vertices[m_Indices[i + 1] * 3 + 1], m_Vertices[m_Indices[i + 1] * 3 + 2]);
		vec3 pos2 = maths::vec3(m_Vertices[m_Indices[i + 2] * 3], m_Vertices[m_Indices[i + 2] * 3 + 1], m_Vertices[m_Indices[i + 2] * 3 + 2]);

		vec2 uv0 = maths::vec2(m_Vertices[m_Indices[i] * 2], m_Vertices[m_Indices[i] * 2 + 1]);
		vec2 uv1 = maths::vec2(m_Vertices[m_Indices[i + 1] * 2], m_Vertices[m_Indices[i + 1] * 2 + 1]);
		vec2 uv2 = maths::vec2(m_Vertices[m_Indices[i + 2] * 2], m_Vertices[m_Indices[i + 2] * 2 + 1]);

		vec3 edge1 = pos1 - pos0;
		vec3 edge2 = pos2 - pos0;

		vec2 deltaUV1 = uv1 - uv0;
		vec2 deltaUV2 = uv2 - uv0;

		float r = (float)(1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x));

		vec3 tangent;
		tangent.x = r * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent.y = r * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent.z = r * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent.normalize();


		vec3 bitangent;
		bitangent.x = r * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent.y = r * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent.z = r * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		bitangent.normalize();

		//arranging the tangents and bitangents in their arrays
		{
			m_Tangents[m_Indices[i] * 3] += tangent.x;
			m_Tangents[m_Indices[i] * 3 + 1] += tangent.y;
			m_Tangents[m_Indices[i] * 3 + 2] += tangent.z;
			m_Bitangents[m_Indices[i] * 3] += bitangent.x;
			m_Bitangents[m_Indices[i] * 3 + 1] += bitangent.y;
			m_Bitangents[m_Indices[i] * 3 + 2] += bitangent.z;

			m_Tangents[(m_Indices[i + 1]) * 3] += tangent.x;
			m_Tangents[(m_Indices[i + 1]) * 3 + 1] += tangent.y;
			m_Tangents[(m_Indices[i + 1]) * 3 + 2] += tangent.z;
			m_Bitangents[(m_Indices[i + 1]) * 3] += bitangent.x;
			m_Bitangents[(m_Indices[i + 1]) * 3 + 1] += bitangent.y;
			m_Bitangents[(m_Indices[i + 1]) * 3 + 2] += bitangent.z;

			m_Tangents[(m_Indices[i + 2]) * 3] += tangent.x;
			m_Tangents[(m_Indices[i + 2]) * 3 + 1] += tangent.y;
			m_Tangents[(m_Indices[i + 2]) * 3 + 2] += tangent.z;
			m_Bitangents[(m_Indices[i + 2]) * 3] += bitangent.x;
			m_Bitangents[(m_Indices[i + 2]) * 3 + 1] += bitangent.y;
			m_Bitangents[(m_Indices[i + 2]) * 3 + 2] += bitangent.z;
		}
	}
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
void MeshResource::setTangents(std::vector<GLfloat> tangents)
{
	m_Tangents = tangents;
}
void MeshResource::setBitangents(std::vector<GLfloat> bittangents)
{
	m_Bitangents = bittangents;
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
auto MeshResource::getTangents() const -> std::vector<GLfloat>
{
	return m_Tangents;
}
auto MeshResource::getBitangents() const -> std::vector<GLfloat>
{
	return m_Bitangents;
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
