#pragma once
#include"PlayerState.h"
class StealthState
	: public PlayerState {
public:


~StealthState();
virtual void entry(PlayerBehavior* playerBehavior) override;
virtual void execute(PlayerBehavior* playerBehavior, float deltaTime);
virtual void exit(PlayerBehavior* playerBehavior) override;
static StealthState* Instance();
private: 
	const float m_HeightOffset; 
	const float m_PlayerSpeedFactor; 
private:
	StealthState();
	void crouchWalk(PlayerBehavior* playerBehavior, float deltaTime);
};