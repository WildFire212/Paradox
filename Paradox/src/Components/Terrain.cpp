#include "Terrain.h"



namespace Paradox {
	namespace component {
			

		Terrain::Terrain(int gridX, int gridZ, Texture* tex, const char* HeightMapLocation) :MeshRenderer(generateTerrain(HeightMapLocation,tex, gridX, gridZ))
		{
		

		}


		 Mesh* Terrain::generateTerrain(const char* HeightMapLocation, Texture* m_TerrainTexture, int gridX, int gridZ)
		{
			
		
			const int MAXPIXELCOLOR  = 256 * 256 * 256;
			const float  TERRAINSIZE  = 30.0f;
			

			m_TerrainSize = TERRAINSIZE; 
			
			m_X = gridX * TERRAINSIZE; 
			m_Z = gridZ * TERRAINSIZE; 
			
			unsigned char* heightMap = stbi_load(HeightMapLocation, &m_Width, &m_Height, &m_Bitdepth, 3);
			if (!heightMap)
			{
				std::cout << "failed to get Height Map data" << std::endl;
			}
			else
				std::cout << "height map loaded successfully" << std::endl;

			m_TexData = heightMap; 
			int VERTEX_COUNT = 200;
			m_VertexCount = VERTEX_COUNT; 
			m_Heights = new float*[VERTEX_COUNT];
			for (size_t i = 0; i < VERTEX_COUNT; i++)
			{
				m_Heights[i] = new float[VERTEX_COUNT]; 
			}		
			

			int count = VERTEX_COUNT * VERTEX_COUNT;
			std::vector<GLfloat> vertices(count * 3);
			
			int indc =6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1) * TERRAINSIZE;
			std::vector<GLushort> indices(indc);
			std::vector<GLfloat> normals(count * 3);
			std::vector<GLfloat> texCoords(count * 2);
			//GLfloat* normals = new GLfloat[count * 3];
			//GLfloat * texCoords = new GLfloat[count * 2];
			//unsigned int* indices = new unsigned int[6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1) * SIZE];
			int vertexPointer = 0;
			for (int i = 0; i < VERTEX_COUNT; i++)
			{
				for (int j = 0; j < VERTEX_COUNT; j++)	
				{
					float x = m_X + (float)j / ((float)VERTEX_COUNT - 1)*TERRAINSIZE;
					vertices[vertexPointer * 3] = x;
					float height = getHeight(j, i, heightMap); 
					m_Heights[j][i] = height; 
					vertices[vertexPointer * 3 + 1] =height ; 
					float z = m_Z + (float)i / ((float)VERTEX_COUNT - 1) * TERRAINSIZE;
 					vertices[vertexPointer * 3 + 2] = z;
					//std::cout << "(      " << vertices[vertexPointer * 3+1]<< "     "<<std::endl;
					vec3 normal = calculateNormal(j, i, heightMap); 
					
					normals[vertexPointer * 3] = normal.x;
					normals[vertexPointer * 3 + 1] = normal.y;
					normals[vertexPointer * 3 + 2] = normal.z;

					texCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
					texCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
					vertexPointer++;


				}
			}
			int pointer = 0;
			for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
			{
				for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
				{
					int topLeft = (gz*VERTEX_COUNT) + gx;
					int topRight = topLeft + 1;
					int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
					int bottomRight = bottomLeft + 1;
					indices[pointer++] = topLeft;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = topRight;
					indices[pointer++] = topRight;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = bottomRight;

				}
			}
			return new Mesh(vertices, indices, count * 3, 6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1) * TERRAINSIZE, texCoords, new Material(*m_TerrainTexture, 0.1f, 0.1f, *m_TerrainTexture), normals, false);



		}

		//void Terrain::render(const RenderingEngine& renderEngine)
		//{
		//	//TerrainTexture.UseTexture();
		//	//TerrainMesh.RenderMesh();
		//	
		//}

		Terrain::~Terrain()
		{
		}

		float Terrain::getHeight(int x, int y, unsigned char * texData) const
		{
			if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
			{
				return 0;
			}

			//get rgb color value 

			unsigned char* pixelOffset = texData + (x + m_Height * y) * 3;
			int r = pixelOffset[0];
			int g = pixelOffset[1];
			int b = pixelOffset[2];

			//int RGB = r   * g  * b ; 
			//RGB += MAXPIXELCOLOR / 2.0f; 
			//RGB /= MAXPIXELCOLOR / 2.0f; 
			//RGB *= MAXHEIGHT; 
			const float  MAXHEIGHT = 4.0f;
			float RGB = r * (MAXHEIGHT / 255.0f);

			return RGB;

		}
		const float Terrain::getHeightOfTerrain(float worldX, float worldZ) const
		{
			float terrainX  = worldX - this->m_X;
			float terrainZ  = worldZ - this->m_Z;

			float gridSquareSize = (float)m_TerrainSize / ((float)m_VertexCount - 1);
			
			int gridX = (int)floor(terrainX / gridSquareSize); 
			int gridZ= (int)floor(terrainZ/ gridSquareSize);

			if (gridX >= m_VertexCount - 1 || gridZ >= m_VertexCount - 1 || gridX < 0 || gridZ < 0)
			{

				return -1.0f; 
			}
			float xCoord = fmod(terrainX , gridSquareSize) / gridSquareSize; 
			float zCoord = fmod(terrainZ ,gridSquareSize) / gridSquareSize; 
			float answer; 
			if (xCoord <= (1 - zCoord)) {
				answer = 
					barryCentric(vec3(0, m_Heights[gridX][gridZ], 0), vec3(1,
						m_Heights[gridX + 1][gridZ], 0), vec3(0,
							m_Heights[gridX][gridZ + 1], 1), vec2(xCoord, zCoord));
			}
			else {
				answer = 
					barryCentric(vec3(1, m_Heights[gridX + 1][gridZ], 0), vec3(1,
						m_Heights[gridX + 1][gridZ + 1], 1), vec3(0,
							m_Heights[gridX][gridZ + 1], 1),vec2(xCoord, zCoord));
			}

			return answer; 
			//float height = getHeight(worldX, worldZ, m_TexData); 
			//return height; 

		}

		const vec3 Terrain::getNormal(float worldX, float worldZ) const
		{
			vec3 normal = calculateNormal((int)worldX, (int)worldZ, m_TexData);
			return normal;
		}

		vec3 Terrain::calculateNormal(int x, int z, unsigned char * texData) const 
		{
			float heightL = getHeight(x - 1, z, texData);
			float heightR = getHeight(x + 1, z, texData);
			float heightD = getHeight(x, z - 1, texData);
			float heightU = getHeight(x, z + 1, texData);
			vec3 normal = vec3(heightL - heightR, 2.f, heightD - heightU);
			normal.normalize();
			return normal;
		}

		const float Terrain::barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos) const {
			float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
			float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
			float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
			float l3 = 1.0f - l1 - l2;
			return l1 * p1.y + l2 * p2.y + l3 * p3.y;
		}

	}
}