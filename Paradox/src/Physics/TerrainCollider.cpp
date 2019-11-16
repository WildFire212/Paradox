#include "TerrainCollider.h"
namespace Paradox {
	namespace physics {

	TerrainCollider::TerrainCollider(const Terrain& terrain) : Collider(TYPE_TERRAIN),
	m_Terrain(terrain) 
	{
		
	}

	IntersectData TerrainCollider::intersectSphereCollider(const SphereCollider & sphereCollider)
	{

		//calculate height from terrain to the sphere at that point 
		float distanceFromCenter =sphereCollider.getCenter().y -  m_Terrain.getHeightOfTerrain(sphereCollider.getCenter().x, sphereCollider.getCenter().z);

		float distanceFromSphere = distanceFromCenter -
			sphereCollider.getRadius();


		//calculate normal at that point 
		//vec3 normal = calcTerrainNormal(sphereCollider.getCenter());

		return IntersectData(distanceFromSphere < 0.0f,vec3(0,0,0) ,distanceFromSphere);
	}

} }
