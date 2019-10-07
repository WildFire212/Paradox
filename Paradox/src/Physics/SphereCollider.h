#pragma once
#include"../maths/maths.h"
#include"Collider.h"
using namespace Paradox::maths; 
namespace Paradox {
	namespace physics {

class SphereCollider : public Collider
{
private: 
	vec3 m_Center;  
	float m_Radius; 
public:

	SphereCollider(vec3 center, float radius); 
	~SphereCollider();
	IntersectData intersectSphereCollider(const SphereCollider& other); 

	//setters 
	void  setRadius(float radius); 
	void setCenter(maths::vec3 center); 
	void setCenter(float x, float y , float z); 

	void transform(const vec3& translation) override;
	//getters
	const float getRadius() const; 
	 const vec3 getCenter()  const override;

private: 

};

	}
}
