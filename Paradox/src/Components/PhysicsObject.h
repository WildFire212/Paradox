#pragma once
#include"../maths/maths.h"
#include"../Components/Component.h"
#include"../Physics/Collider.h"

using namespace Paradox::maths;
using namespace Paradox::physics; 
namespace Paradox {
	namespace component {
		
class PhysicsObject : public Component
{
private: 
	Collider* m_Collider; 
	vec3 m_Position; 
	vec3 m_OldPosition; 
	vec3 m_Velocity; 
	float m_Mass; 
public: 
	vec3 m_CurrAcceleration;
	bool m_UseGravity; 
	bool m_CurrUseGravity; 
public:
	explicit PhysicsObject(Collider* collider, float mass, vec3 velocity, bool isGravity);
	~PhysicsObject();

	explicit PhysicsObject(vec3 position, float mass, vec3 velocity); 
	void integrate(float deltaTime); 

	void addForce(vec3 force); 
	//overriden functions 
	void update(float deltaTime) override; 
	//getters 
	inline const vec3 getPosition() const {
		return m_Position;
	}
	inline const vec3 getVelocity() const {
		return m_Velocity; 
	}
	inline Collider& getCollider() {
		vec3 translation = m_Position - m_OldPosition; 
		m_OldPosition = m_Position;		
		m_Collider->transform(translation); 
		return *m_Collider; 
	}

	inline const float getMass() const {
		return m_Mass; 
	}
	//setters 
	void setVelocity(vec3 velocity);
	void setPosition(vec3 position); 
	void setMass(float Mass); 
	
	
};

} }
