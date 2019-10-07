#pragma once
#pragma once
#include"../../Components/Behavior.h"	
using namespace Paradox::component;
class BallBehavior : public Behavior
{
private:
public:
	BallBehavior();
	const float coolDownTime;
	void update(float deltaTime) override;
private:

};