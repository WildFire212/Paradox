#include "PhysicsObject.h"
#include"../core/GameObject.h"

namespace Paradox {
	namespace component {

		PhysicsObject::PhysicsObject(Collider * collider, float mass, vec3 velocity,bool isGravity):
			m_Collider(collider),
			m_Position(collider->getCenter()),
			m_OldPosition(collider->getCenter()),
			m_Velocity(velocity),
			m_UseGravity(isGravity),
			m_CurrAcceleration(0.0f),
			m_Mass(mass),
			m_CurrUseGravity(true)
		{
			
		}

		PhysicsObject::~PhysicsObject()
		{
		}
	
		PhysicsObject::PhysicsObject(vec3 position,float mass,  vec3 velocity)
		{
			m_Position = position; 
			m_Velocity = velocity; 
			m_UseGravity = false; 
			m_CurrAcceleration = 0.0f; 
			m_Mass = mass; 
			m_CurrUseGravity = true; 
		}

		void PhysicsObject::integrate(float deltaTime)
		{
			m_Position += m_Velocity * deltaTime; 
		}
		void PhysicsObject::addForce(vec3 force)
		{
			
			m_CurrAcceleration += force  /m_Mass; 

		}
		void PhysicsObject::update(float deltaTime)
		{
			//m_Position.x = m_Parent->getTransform()->translation.x;
			//m_Position.z = m_Parent->getTransform()->translation.z;
			m_Position = m_Parent->getTransform()->translation; 
			float U = 0.0f;
				if (m_UseGravity == true && m_Position.y  > 0.0f && m_CurrUseGravity)
				{
					U = m_Mass * 0.8f;
					//addForce(vec3(0.0f, -U, 0.f));
					addForce(m_Mass * vec3(0.0f, -9.8f,0.0f)); 
					//m_Velocity = m_Velocity + (m_CurrAcceleration )* deltaTime;
							
				}	



				m_Velocity = m_Velocity + (m_CurrAcceleration)* deltaTime;
				integrate(deltaTime); 
			this->m_Parent->getTransform()->setTranslation(getPosition());
			m_CurrAcceleration = 0.0f; 
			m_CurrUseGravity = true; 
			
		}
		void PhysicsObject::setVelocity(vec3 velocity)
		{
			m_Velocity = velocity; 
			
		}

		void PhysicsObject::setPosition(vec3 position)
		{
			m_Position = m_Parent->getTransform()->translation = position; 
		}

		void PhysicsObject::setMass(float Mass)
		{
			m_Mass = Mass; 
		}
		
	}
}