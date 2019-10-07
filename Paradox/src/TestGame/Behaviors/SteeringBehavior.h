#pragma once
#include"../../core/Scene.h"
#include"../../Components/Behavior.h"	
#include<list>
using namespace Paradox::component; 
class SteeringBehavior : public Behavior {
public : 
	float m_MaxSpeed;
	vec3 m_Velocity;
	vec3 m_Heading;
private: 
	Scene& m_Scene; 
	//follow path
	std::list<vec3> m_WayPoints; 
	vec3 m_CurrWayPoint;  
	std::list<vec3>::iterator m_CurrWayPointIterator; 
	
public: 
	//constr and destr
	SteeringBehavior(Scene& scene);
	~SteeringBehavior() ;
	
	void update(float deltaTime) override;
	void addToList(vec3 wayPoint); 
private: 
	vec3 seek(vec3 TargetPos); 
	//void arrive(); 
	vec3 followPath(); 
	vec3 Pursuit(vec3 TargetPosition, float speed); 
	



};