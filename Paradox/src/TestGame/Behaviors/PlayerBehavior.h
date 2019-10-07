#pragma once
#include"../../Components/Behavior.h"	
class PlayerState; 
using namespace Paradox::component; 
class PlayerBehavior : public Behavior
{
public: 
	float m_MaxSpeed;
	vec3 m_Velocity; 
	vec3 m_Heading; 
private: 
public :
	PlayerBehavior(); 
	~PlayerBehavior(); 
	void update(float deltaTime) override; 
	void changeState(PlayerState* newState); 
	

private: 
	PlayerState* m_PlayerState; //cause we want  to change state
};