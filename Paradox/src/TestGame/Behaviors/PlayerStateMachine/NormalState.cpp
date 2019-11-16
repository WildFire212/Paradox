#include"NormalState.h"
#include"StealthState.h"
NormalState::NormalState() : 
m_NormalState(NormalStates::Walking){

}
NormalState::~NormalState() {


}
void NormalState::entry(PlayerBehavior* playerBehavior) 
{
	std::cout << "NORMAL STATE" << std::endl; 
	this->timer  = Time::getTime() / Time::SECONDS;
}
void NormalState::execute(PlayerBehavior* playerBehavior, float deltaTime) {

	if (Input::getKey(GLFW_KEY_T) && !Input::getKey(GLFW_KEY_LEFT_SHIFT))
	{
		//std::cout << "WALKING" << std::endl;
		walk(playerBehavior, deltaTime); 

	}
	if (Input::getKey(GLFW_KEY_T) && Input::getKey(GLFW_KEY_LEFT_SHIFT))
	{
		//std::cout << "RUNNING" << std::endl;
		run(playerBehavior, deltaTime); 
	}

	float elasped= (Time::getTime() / Time::SECONDS) - timer; 
	if (elasped> 0.0f)
	{
		
	if (Input::getKey(GLFW_KEY_C))
	{
		
		playerBehavior->changeState(StealthState::Instance());
	}
	}
	
}
void NormalState::exit(PlayerBehavior* playerBehavior) {}
NormalState* NormalState::Instance() {
	static NormalState instance;
	
	return &instance;
}

void NormalState::run(PlayerBehavior* playerBehavior, float deltaTime)
{
	static bool first = true; 
	//up 
	if (first) {

	playerBehavior->getTransform()->move(
		maths::vec3(playerBehavior->m_Parent->getComponent<Camera>()->getFront().x, 2.0f, playerBehavior->m_Parent->getComponent<Camera>()->getFront().z) *1.5f*playerBehavior->m_MaxSpeed* deltaTime);
	first = false; 

	}
	//down
	else 
	{
		playerBehavior->getTransform()->move(
			maths::vec3(playerBehavior->m_Parent->getComponent<Camera>()->getFront().x, -2.0f, playerBehavior->m_Parent->getComponent<Camera>()->getFront().z) *1.5f*playerBehavior->m_MaxSpeed * deltaTime);
		first = true; 
	}

}

void NormalState::walk(PlayerBehavior * playerBehavior, float deltaTime)
{
	
	playerBehavior->getTransform()->move(
	maths::vec3(playerBehavior->m_Parent->getComponent<Camera>()->getFront().x , 0.0f,playerBehavior->m_Parent->getComponent<Camera>()->getFront().z) * playerBehavior->m_MaxSpeed * deltaTime);
}