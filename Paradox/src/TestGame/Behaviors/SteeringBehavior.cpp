#include "SteeringBehavior.h"
#include"../../Components/PhysicsObject.h"
SteeringBehavior::SteeringBehavior(Scene& scene) :
	m_Scene(scene),
	m_MaxSpeed(2.0f),
	m_Velocity(0.f, 0.f, 0.f),
	m_Heading(0.0f, 0.f, 0.f)
{
	m_WayPoints.push_back(vec3(-1000,-1000,-1000));

	m_CurrWayPointIterator = m_WayPoints.begin(); 
}


SteeringBehavior::~SteeringBehavior()
{
}

void SteeringBehavior::update(float deltaTime)
{
	//m_Velocity = Pursuit(m_Scene.findObject("Ball")->getTransform()->getTranslation(),4.0f);
	m_Velocity = followPath();
	getTransform()->move (vec3(m_Velocity.x* deltaTime,0.0f , m_Velocity.z * deltaTime));
	//getTransform()->move (vec3(m_Velocity.x* deltaTime,0.0f , m_Velocity.y * deltaTime));
}

void SteeringBehavior::addToList(vec3 wayPoint)
{
	std::list<vec3>::iterator it = m_WayPoints.begin();
	if (*it == vec3(-1000,-1000,-1000))
	{
		m_WayPoints.pop_back(); 
		m_WayPoints.push_back(wayPoint); 
		m_CurrWayPointIterator = m_WayPoints.begin();	//need to change iterator as the element inserted earlier ws deleted
		return; 
	}
	m_WayPoints.push_back(wayPoint);

}

vec3 SteeringBehavior::seek(vec3 TargetPos)
{
	vec3 desiredVelocity = TargetPos - getTransform()->getTranslation();
	desiredVelocity.normalize(); 
	
	return m_Velocity = desiredVelocity * m_MaxSpeed ;
	
	
}

vec3 SteeringBehavior::followPath()
{
	
	vec3 toCurrWayPoint = *m_CurrWayPointIterator - getTransform()->getTranslation() ;
	bool pathFinished = false; 
	float l = toCurrWayPoint.length();
	if ( 0.0f < l && l < 1.0f)
	{
		std::advance(m_CurrWayPointIterator, 1); 
		if (m_CurrWayPointIterator == m_WayPoints.end())
		{
			m_CurrWayPointIterator = m_WayPoints.begin();
		}
		//pathFinished = true; 
	}
	else
	{
		pathFinished = false; 
	}

	if (pathFinished == false)
	{
		return seek(*m_CurrWayPointIterator);
	}
	

}

vec3 SteeringBehavior::Pursuit(vec3 TargetPosition, float speed)
{
	//consider evader	
	vec3 toEvader = TargetPosition - getTransform()->getTranslation();
	//dot product of front of evader and zombie 
	// > 0 then chase without changing the direction

	//now dont consider that in the same direction 
	float lookAheadTime = toEvader.length() / (m_MaxSpeed + speed);
	return seek(TargetPosition + m_Heading * lookAheadTime);
}

