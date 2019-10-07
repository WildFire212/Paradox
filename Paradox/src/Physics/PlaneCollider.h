#pragma once

#include"../maths/maths.h"
#include"SphereCollider.h"

using namespace Paradox::maths; 
namespace Paradox {
	namespace physics {

class PlaneCollider : public Collider
{
private: 
	vec3 m_Normal; 
	float m_Distance; 
public:
	

	~PlaneCollider();
	explicit PlaneCollider(vec3 normal, float distance); 

	//normalize
	void normalize(); 

	IntersectData intersectSphereCollider(const SphereCollider& sphereCollider);
	//getters 
	inline const vec3 getNormal() const {
		return m_Normal; 
	}
	inline const float getDistance() const {
		return m_Distance; 
	}

};

 

} }
