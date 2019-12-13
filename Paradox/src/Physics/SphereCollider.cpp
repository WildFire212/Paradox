#include "SphereCollider.h"

namespace Paradox {
	namespace physics {




SphereCollider::SphereCollider(vec3 center, float radius) : Collider(TYPE_SPHERE)
{
	m_Center = center; 
	m_Radius = radius;
	//m_ColliderType = TYPE_SPHERE; 
	m_tempRad = radius; 
}


SphereCollider::~SphereCollider()
{
}

IntersectData SphereCollider::intersectSphereCollider(const SphereCollider & other)
{
	// sum of radii of the 2 spheres 
	float radiusDistance = m_Radius + other.getRadius();

	//distance b/w centers of the 2 spheres 
	vec3 direction= (other.getCenter() - m_Center); 
	
	float centerDistance = direction.length(); 

	direction =direction/ centerDistance; 
	//actual distance b/w the spheres 
	float distance = centerDistance - radiusDistance; 

	return IntersectData(distance < 0, direction ,distance); 
}
void SphereCollider::setRadius(float radius)
{
	m_Radius = radius; 
	m_tempRad = radius; 
}
void SphereCollider::setCenter(maths::vec3 center)
{
	m_Center = center; 
}
void SphereCollider::setCenter(float x, float y, float z)
{
	m_Center.x = x; 
	m_Center.y = y;
	m_Center.z = z;
}
void SphereCollider::transform(const vec3 & translation,const vec3& scaling)
{
	m_Center += translation;	
	//m_Radius = m_tempRad*scaling.x; 
	m_Scale= scaling; 
	m_Radius = m_tempRad*m_Scale.x; 

}
const float SphereCollider::getRadius()  const
{
	return m_Radius; 
}
const vec3 SphereCollider::getCenter()  const 
{
	return m_Center; 
}
} }
