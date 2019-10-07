#include "AABBCollider.h"


namespace Paradox {
	namespace physics {



AABBCollider::~AABBCollider()
{
}
AABBCollider::AABBCollider(vec3 minBounds, vec3 maxBounds) : Collider(TYPE_AABB)
{

	m_MaxBounds = maxBounds; 
	m_MinBounds = minBounds; 

}
IntersectData AABBCollider::intersectAABB(const AABBCollider & other)
{
	vec3 distances1 = m_MinBounds - other.getMaxBounds();
	vec3 distances2= other.getMinBounds() - m_MaxBounds; 

	vec3 distances = distances1.Max(distances2); 
	
	float maxDistance = distances.Max(); 

	return IntersectData(maxDistance < 0, maxDistance);
}
} }
