#include"NormalState.h"
#include"StealthState.h"


StealthState::StealthState() :
	m_HeightOffset(2.0f),
	m_PlayerSpeedFactor(0.5f) 
{
	
}
StealthState::~StealthState() {


}
void StealthState::entry(PlayerBehavior* playerBehavior) {
	std::cout << "STEALTH STATE" << std::endl;
	this->timer = Time::getTime() / Time::SECONDS;
	playerBehavior->m_Parent->getTransform()->move(vec3(0.0f,-m_HeightOffset,0.0f)); 
		

}
void StealthState::execute(PlayerBehavior* playerBehavior,float deltaTime) {

	if (Input::getKey(GLFW_KEY_T) && !Input::getKey(GLFW_KEY_LEFT_SHIFT))
	{
		//std::cout << "WALKING" << std::endl;
		crouchWalk(playerBehavior, deltaTime);

	}
	float elasped = (Time::getTime() / Time::SECONDS) - timer;
	if (elasped > 0.0f)
	{

		if (Input::getKey(GLFW_KEY_C)   || (Input::getKey(GLFW_KEY_LEFT_SHIFT)) and (Input::getKey(GLFW_KEY_T)))
		{
			
			playerBehavior->changeState(NormalState::Instance());
		}
	
	}
}
void StealthState::exit(PlayerBehavior* playerBehavior)  {
	playerBehavior->getTransform()->move(vec3(0, m_HeightOffset,0));

}
StealthState* StealthState::Instance() {
	static StealthState instance;
	return &instance;
}

void StealthState::crouchWalk(PlayerBehavior * playerBehavior, float deltaTime)
{
	playerBehavior->getTransform()->move(
		maths::vec3(playerBehavior->m_Parent->getComponent<Camera>()->getFront().x, 0.0f, playerBehavior->m_Parent->getComponent<Camera>()->getFront().z) * playerBehavior->m_MaxSpeed* m_PlayerSpeedFactor* deltaTime);
	
}
