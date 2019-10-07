#pragma once
#include"../maths/maths.h"
#include"Collider.h"
using namespace Paradox::maths; 
namespace Paradox {
	namespace physics {

class AABBCollider : public Collider
{
private: 
	vec3 m_MaxBounds; 
	vec3 m_MinBounds; 
public:

	~AABBCollider();
	
	explicit AABBCollider(vec3 minBounds, vec3 maxBounds); 

	IntersectData intersectAABB(const AABBCollider& other); 

	//getter 
	inline const vec3 getMinBounds() const {
		return m_MinBounds; 
	}
	inline const vec3 getMaxBounds() const {
		return m_MaxBounds; 
	}
	
};

} }
