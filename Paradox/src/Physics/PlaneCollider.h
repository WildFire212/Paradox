#pragma once

#include"../maths/maths.h"
#include"SphereCollider.h"
#include"AABBCollider.h"
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

	auto intersectSphereCollider(const SphereCollider& sphereCollider) -> IntersectData;
	auto intersectAABBCollider(const AABBCollider& aabbCollider)->IntersectData; 
	//getters 
	inline auto getNormal() const -> const vec3 {
		return m_Normal; 
	}
	inline auto getDistance() const -> const float {
		return m_Distance; 
	}

};

 

} }
