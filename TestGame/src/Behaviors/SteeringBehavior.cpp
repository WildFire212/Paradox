#include "SteeringBehavior.h"
#include"Components/PhysicsObject.h"
SteeringBehavior::SteeringBehavior(Scene& scene) :
	m_Scene(scene),
	m_MaxSpeed(2.0f),
	m_Velocity(0.f, 0.f, 0.f),
	m_Heading(0.0f, 0.f, 0.f),
	m_Forward(0, 0, 0),
	m_DistanceToSearch(13.0f)
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
	vec3 playerPosition = m_Scene.findObject("Player")->getTransform()->getTranslation();
	static int coolDownSearch = 0; 
	
	
		//if coolDown = 0 : time to search
		if (coolDownSearch == 0)
		{
			if (searchPlayer(vec2(playerPosition.x, playerPosition.z)))
			{
				coolDownSearch++;	//if found then stop searching 

			}
			
			else{
			m_Velocity = followPath();	//if not found then keep following path
			}
		}
		//if coolDown !=0 : time to chase player 
		else if (coolDownSearch != 0)
		{
			coolDownSearch++; 
			m_Velocity = Pursuit(playerPosition, 4.0f);		//chase player 
			if (coolDownSearch > 1000)
			{
				coolDownSearch = 0 ;			//if coolDown done again search 

			}
		}
	
	//	m_Velocity = followPath();
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
	m_Forward = toCurrWayPoint;
	m_Forward.normalize(); 
	m_Forward.y = 0;
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
	m_Forward = toEvader; 
	m_Forward.normalize();
	m_Forward.y = 0;
	//dot product of front of evader and zombie 
	// > 0 then chase without changing the direction

	//now dont consider that in the same direction 
	float lookAheadTime = toEvader.length() / (m_MaxSpeed + speed);
	return seek(TargetPosition + m_Heading * lookAheadTime);
}

auto SteeringBehavior::searchPlayer(vec2 playerPosition) -> bool
{
	//point inside the triangle calculation for player search 
	float base = (m_Parent->getTransform()->getTranslation() + (m_Forward * m_DistanceToSearch) - m_Parent->getTransform()->getTranslation()).length();
	float half_l2rLen = tan(glm::radians(60.0f)) * base; 
	vec3 temp = m_Forward; 
	temp = temp.cross(vec3(0, 1, 0)); 
	temp.normalize(); 
	vec3 leftPoint = m_Parent->getTransform()->getTranslation() + (m_Forward * m_DistanceToSearch) + temp * base;
	
	temp = m_Forward; 
	temp =(vec3(0, 1, 0).cross(m_Forward)); 
	temp.normalize(); 
	vec3 rightPoint = m_Parent->getTransform()->getTranslation() + (m_Forward * m_DistanceToSearch) + temp * base;
	auto area = [=](float x1, float y1, float x2, float  y2, float  x3,float y3) ->float
	{
		return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2))/2.0f);
	};
	vec3 position = m_Parent->getTransform()->getTranslation(); 
	float A = area(leftPoint.x, leftPoint.z, position.x, position.z, rightPoint.x, rightPoint.z);
	float A1 = area(playerPosition.x, playerPosition.y, position.x, position.z, rightPoint.x, rightPoint.z);
	float A2 = area(leftPoint.x, leftPoint.z, playerPosition.x, playerPosition.y, rightPoint.x, rightPoint.z);
	float A3 = area(leftPoint.x, leftPoint.z, position.x, position.z, playerPosition.x, playerPosition.y);
	return (A == A1 + A2 + A3); 
}

