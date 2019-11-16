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
	}
}