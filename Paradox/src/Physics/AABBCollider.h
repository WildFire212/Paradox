#pragma once
#include"../maths/maths.h"
#include"Collider.h"

using namespace Paradox::maths; 
namespace Paradox {
	namespace physics {
		class SphereCollider; 
class AABBCollider : public Collider
{
private: 
	vec3 m_MaxBounds; 
	vec3 m_MinBounds; 
	enum Direction {
	//	UP, 
	//	DOWN,
		XMAX,
		XMIN, 
		ZMAX , 
		ZMIN
	};

	vec3* m_Directions;
public:
	
	~AABBCollider();
	
	explicit AABBCollider(vec3 minBounds, vec3 maxBounds); 

	IntersectData intersectAABB(const AABBCollider& other); 

	// this test for determining the closest Point on AABB to a certain Point.
	double squaredDistPointAABB(const vec3& point, const AABBCollider& aabb);
	//closest point on aabb to this point
	vec3 closestPointOnAABB(const vec3& point) const; 
	//get Direction according to point
	Direction vectorDirection(const SphereCollider& other) const; 
	//AABB
	IntersectData intersectSphereCollider(const SphereCollider& other);
	
	//getter 
	inline const vec3 getMinBounds() const {
		return m_MinBounds; 
	}
	inline const vec3 getMaxBounds() const {
		return m_MaxBounds; 
	}

	//overrided
	void transform(const vec3& translation)	override; 
	
};

} }
