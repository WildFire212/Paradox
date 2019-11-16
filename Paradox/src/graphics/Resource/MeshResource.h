#pragma once
#include"GL/glew.h"
#include<vector>
#include"../../Components/Material.h"
namespace Paradox {
	namespace graphics {

class MeshResource
{
private: 
	std::vector<GLfloat> m_Vertices;
	std::vector<GLushort> m_Indices;

	std::vector<GLfloat> m_Normals;
	std::vector<GLfloat> m_TexCoords;

	Material* m_Material; 

	GLuint m_VertexCount;
	GLuint m_IndexCount;
	
public:
	MeshResource();
	MeshResource(std::vector<GLfloat> vertices, std::vector<GLushort> indices, std::vector<GLfloat> texCoords, std::vector<GLfloat> normals,Material* material);
	~MeshResource();

	
	void setVertices(std::vector<GLfloat> vertices);
	void setIndices(std::vector<GLushort> indices); 
	void setTexCoords(std::vector<GLfloat> texCoords);
	void setNormals(std::vector<GLfloat> normals);
	void setVertexCount(GLuint vertexCount); 
	void setIndexCount(GLuint indexCount);
	void setMaterial(Material* material);
	
	//getters
	auto getVertices() const -> std::vector<GLfloat>;
	auto getIndices() const -> std::vector<GLushort>;
	auto getTexCoords() const -> std::vector<GLfloat>;
	auto getNormals() const -> std::vector<GLfloat>;
	auto getTexCoordCount() const -> GLuint;
	auto getMaterial() const -> const Material&; 

	auto getVertexCount() const -> GLuint; 
	auto getIndexCount() const -> GLuint; 

};
} }

