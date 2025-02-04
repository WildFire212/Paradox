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
	 vec3 m_Translation; 
	 vec3 m_Scale; 
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
		m_PhysicsMaterial(physicsMaterial),
		m_Translation(vec3(0, 0, 0)),
		m_Scale(vec3(1, 1, 1))
	{
	
	}
	explicit Collider(ColliderType colliderType):
	m_ColliderType(colliderType) ,
		m_Translation(vec3(0, 0, 0)),
	m_Scale(vec3(1, 1, 1))
	{
		m_PhysicsMaterial = new PhysicsMaterial(0.4F, 0.4F, 0.0F);
		
	}

	~Collider() = default;

	 auto Intersect(const Collider& other) -> IntersectData;
	

	 virtual void transform(const vec3& translation,const vec3& scaling) {}

	inline auto getType() const -> const ColliderType& {
		return m_ColliderType; 
	}
	//virtual functions should be inlined when not a reference or pointer used 
	//fully contained object inside a composite
	//when the compiler knows the "exact class" of the object which is the target of the virtual function call.
	virtual  auto getCenter() const -> const vec3 { return vec3(0.0F, 0.0F, 0.0F); }

	//setters
	void setPhysicsMaterial(const PhysicsMaterial* physicsMaterial) ; 

	//getters 
	inline auto getPhysicsMaterial() const -> const PhysicsMaterial& {
		return *m_PhysicsMaterial; 
	}
};

} }
