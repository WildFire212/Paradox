#include "BallBehavior.h"
#include"../../Components/PhysicsObject.h"
#include<iostream>
#include"../../core/GameObject.h"
#include"../../Components/Transform.h"
BallBehavior::BallBehavior(): 
	coolDownTime(2.0f)
{
	
}
void BallBehavior::update(float deltaTime)
{
	static float timer = 0.0f; 
	timer -= deltaTime; 
	vec3 direction = vec3(0,0,0);
	if (timer < 0.0f)
	{
		
		if (Input::getKey(GLFW_KEY_W))
		{
			//when friction comes into play 
			//this->m_Parent->getComponent<PhysicsObject>()->addForce(vec3(1.0f,0,0));
			this->m_Parent->move(vec3(0.1f, 0.0f, 0)); 
			direction += vec3(0.1f, 0.0f, 0.0f); 
		}if (Input::getKey(GLFW_KEY_S))
		{
			//when friction comes into play 
		//this->m_Parent->getComponent<PhysicsObject>()->addForce(vec3(1.0f,0,0));
			this->m_Parent->move(vec3(-0.1f, 0.0f, 0));
			direction += vec3(-0.1f, 0.0f, 0.0f);

		}if (Input::getKey(GLFW_KEY_D))
		{
			//when friction comes into play 
			//this->m_Parent->getComponent<PhysicsObject>()->addForce(vec3(0.0f,0,6.0f));
			this->m_Parent->move(vec3(0.0f, 0.0f, 0.1f));
			direction += vec3(0.0f, 0.0f, 0.1f);

		}if (Input::getKey(GLFW_KEY_A))
		{
			//when friction comes into play 
		//this->m_Parent->getComponent<PhysicsObject>()->addForce(vec3(1.0f,0,0));
			this->m_Parent->move(vec3(0.0f, 0.0f, -0.1f));
			direction += vec3(0.0f, 0.0f, -0.1f);

		}
	//	std::cout << "The posiiton of the player is " << this->m_Parent->getTransform()->getTranslation().x
	//<<" "<< this->m_Parent->getTransform()->getTranslation().y
	//<< " " << this->m_Parent->getTransform()->getTranslation().z << std::endl;

		if (Input::getKey(GLFW_KEY_SPACE))
		{
		//this->m_Parent->getComponent<Paradox::component::PhysicsObject>()->setVelocity(vec3(5.0f,0.0f,0.0f));
		this->m_Parent->getComponent<PhysicsObject>()->addForce(vec3(0.0f, 5000.8f, 0.0f)); 
		//this->m_Parent->getTransform()->translation += direction; 
		timer = coolDownTime; 
		

		}
	
	}

}