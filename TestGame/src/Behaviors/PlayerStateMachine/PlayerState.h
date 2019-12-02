#pragma once
#include"../PlayerBehavior.h"
#include"core/Time.h"
class PlayerState {
protected : 
	float timer; 
public: 
	PlayerState() {
		timer = Time::getTime()/Time::SECONDS; 
		
	}
	~PlayerState(){}
	virtual void execute(PlayerBehavior* playerBehavior,float deltaTime) = 0; 
	virtual void entry(PlayerBehavior* playerBehavior) = 0; 
	virtual void exit(PlayerBehavior* playerBehavior) = 0; 
	
		
};