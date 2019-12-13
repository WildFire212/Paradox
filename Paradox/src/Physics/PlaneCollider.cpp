#include "PlaneCollider.h"

namespace Paradox {
	namespace physics {



		PlaneCollider::~PlaneCollider()
		{
		}
		PlaneCollider::PlaneCollider(vec3 normal, float distance) : Collider(TYPE_PLANE)
		{
			m_Normal = normal; 
			m_Distance = distance; 
			normalize(); 
		}
		void PlaneCollider::normalize()
		{
			float magnitude  = m_Normal.length(); 
			m_Normal = m_Normal / magnitude; 
			m_Distance = m_Distance / magnitude;
		}

		IntersectData PlaneCollider::intersectSphereCollider(const SphereCollider & sphereCollider)
		{
			float distanceFromCenter = (float)fabs(m_Normal.dot(sphereCollider.getCenter()) - m_Distance);
			
			
			float distanceFromSphere = distanceFromCenter - sphereCollider.getRadius(); 


			return IntersectData(distanceFromSphere < 0.0f , m_Normal,distanceFromSphere);
		}
		auto PlaneCollider::intersectAABBCollider(const AABBCollider& aabbCollider) -> IntersectData
		{
			vec3 c = (aabbCollider.getMaxBounds()+ aabbCollider.getMinBounds()) * 0.5f; // Compute AABB center
			vec3 e = aabbCollider.getMaxBounds() - c; // Compute positive extents


			// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
			float r = e.x * abs(m_Normal.x) + e.y* abs(m_Normal.y) + e.z* abs(m_Normal.z);

			// Compute distance of box center from plane
			float distance = m_Normal.dot(c) - m_Distance;
			float s = aabbCollider.getMinBounds().y - m_Distance; 
			// Intersection occurs when distance s falls within [-r,+r] interval
			//return IntersectData(abs(distance )<= r,m_Normal, abs(r - distance));
			return IntersectData(s <= 0 ,m_Normal,abs(s));
		}
	}
}