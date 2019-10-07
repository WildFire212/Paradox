#pragma once
#include"IntersectData.h"
#include<stdexcept>
#include<iostream>
#include"PhysicsMaterial.h"
namespace Paradox {
	namespace physics {

class Collider
{
	
protected : 
	 PhysicsMaterial const *  m_PhysicsMaterial; 
public : 
	enum ColliderType {
		TYPE_SPHERE,
		TYPE_AABB,
		TYPE_PLANE,
		TYPE_TERRAIN
	};

public: 
	ColliderType m_ColliderType; 
public:
	explicit Collider(ColliderType colliderType,const PhysicsMaterial* physicsMaterial):
	m_ColliderType(colliderType) ,
		m_PhysicsMaterial(physicsMaterial)
	{
	
	}
	explicit Collider(ColliderType colliderType):
	m_ColliderType(colliderType) 
	{
		m_PhysicsMaterial = new PhysicsMaterial(0.4f, 0.4f, 0.0f);
	}

	~Collider() {}

	 IntersectData Intersect(const Collider& other);
	

	virtual void transform(const vec3& translation) {}

	inline const ColliderType& getType() const {
		return m_ColliderType; 
	}
	//virtual functions should be inlined when not a reference or pointer used 
	//fully contained object inside a composite
	//when the compiler knows the "exact class" of the object which is the target of the virtual function call.
	virtual const vec3 getCenter() const { return vec3(0.0f, 0.0f, 0.0f); }

	//setters
	void setPhysicsMaterial(const PhysicsMaterial* physicsMaterial) ; 

	//getters 
	inline const PhysicsMaterial& getPhysicsMaterial() const {
		return *m_PhysicsMaterial; 
	}
};

} }
