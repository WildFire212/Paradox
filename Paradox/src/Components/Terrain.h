#pragma once
#include"../../src/graphics/Texture.h"
#include<string>
#include"MeshRenderer.h"
#include"../Components/Component.h"
#include<vector>
#include"../maths/maths.h"

using namespace Paradox::graphics; 
using namespace Paradox::maths; 
namespace Paradox {
	
	
	
	namespace component {

class Terrain : public MeshRenderer
{
private:

	float** m_Heights ;
	
	auto getHeight(int x, int y, unsigned char* texData) const -> float;

	//Texture* m_TerrainTexture; 
	MeshRenderer* m_TerrainMesh;
	//Height Map components
	int m_Width, m_Height, m_Bitdepth;
	//terrain X and Z 
	float m_X, m_Z; 

	float m_TerrainSize; 
	int m_VertexCount; 

	//image 
	unsigned char* m_TexData; 

public:
	Terrain(int gridX, int gridZ,Texture* texture, const char* HeightMapLocation);
	//float x;
	//float z;

	 auto generateTerrain(const char* HeightMapLocation,Texture* m_TerrainTexture, int gridX, int gridZ) -> Mesh*;
	auto getHeightOfTerrain(float worldX, float worldZ) const -> const float; 
	auto getNormal(float worldX, float worldZ) const -> const vec3; 
	
	//void render(const RenderingEngine& renderEngine) override;
	~Terrain();
private: 

	auto calculateNormal(int x, int z, unsigned char* texData) const -> vec3;
	auto barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos) const -> const float;
};

} }
