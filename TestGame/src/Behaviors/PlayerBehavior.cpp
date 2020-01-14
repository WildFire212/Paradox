#include "PlayerBehavior.h"
#include"PlayerStateMachine/PlayerState.h"
#include"PlayerStateMachine/NormalState.h"
#include"core/Input.h"
#include"Components/PhysicsObject.h"
PlayerBehavior::PlayerBehavior():
	coolDownTime(2.0f)
{
	m_MaxSpeed =20.0f;
	m_PlayerState = NormalState::Instance(); 
	 
}
PlayerBehavior::~PlayerBehavior()
{
}
void PlayerBehavior::update(float deltaTime)
{
	m_Heading = this->m_Parent->getComponent<Camera>()->getFront();
	m_PlayerState->execute(this,deltaTime); 
	vec3 translate(0.0f, 0.0f, 0.0f);
	static float timer = 0.0f;
	timer -= deltaTime;
	vec3 direction = vec3(0, 0, 0);
	
		if (Input::getKey(GLFW_KEY_UP))
		{
			//this->m_Parent->getComponent<Paradox::component::PhysicsObject>()->setVelocity(vec3(5.0f,0.0f,0.0f));
			m_Velocity = m_Heading * m_MaxSpeed;
			translate = m_Velocity * deltaTime;

		}
		if (Input::getKey(GLFW_KEY_DOWN))
		{
			//this->m_Parent->getComponent<Paradox::component::PhysicsObject>()->setVelocity(vec3(-5.f, 0.0f, 0.0f));
			m_Velocity = m_Heading * -m_MaxSpeed;
			translate = m_Velocity * deltaTime;
		}
		//if (Input::getKey(GLFW_KEY_RIGHT))
		//{
		//	//this->m_Parent->getComponent<Paradox::component::PhysicsObject>()->setVelocity(vec3(0.0f, 0.0f, 5.0f));
		//	vec3 translate = this->m_Parent->getComponent<Camera>()->getPosition() - this->m_Parent->getComponent<Camera>()-//>getFront() * -0.1f;
		//	this->m_Parent->getTransform()->setTranslation(m_Parent->getTransform()->translation + translate);
		//}
		//if (Input::getKey(GLFW_KEY_LEFT))
		//{
		//	//this->m_Parent->getComponent<Paradox::component::PhysicsObject>()->setVelocity(vec3(0.0f, 0.0f, -5.0f));
		//	vec3 translate = this->m_Parent->getComponent<Camera>()->getPosition() - this->m_Parent->getComponent<Camera>()-//>getFront() * -0.1f;
		//	this->m_Parent->getTransform()->setTranslation(m_Parent->getTransform()->translation + translate);
		//}
		if (timer < 0.0f)
		{
		if (Input::getKey(GLFW_KEY_SPACE))
		{
			//this->m_Parent->getComponent<Paradox::component::PhysicsObject>()->setVelocity(vec3(5.0f,0.0f,0.0f));
			this->m_Parent->getComponent<Paradox::component::PhysicsObject>()->addForce(vec3(0.0f, 10000.8f, 0.0f));
			//this->m_Parent->getTransform()->translation += direction; 
			timer = coolDownTime;


		}
	}
	//this->m_Parent->move(vec3(translate.x,0,translate.z));
	this->m_Parent->getTransform()->move(translate);
}

void PlayerBehavior::changeState(PlayerState * newState)
{
	if (m_PlayerState != nullptr)
	{
		//cause then m_PlayerSTate points to nothing therefore first let the pointer be nullptr 
	m_PlayerState->exit(this); 
	m_PlayerState = nullptr; 
	delete m_PlayerState; 
	m_PlayerState = newState; 
	m_PlayerState->entry(this); 
	}
}

