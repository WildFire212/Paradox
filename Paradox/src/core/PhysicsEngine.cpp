#include "PhysicsEngine.h"
#include"../Physics/PlaneCollider.h"
#include"../Physics/TerrainCollider.h"	
namespace Paradox {
	namespace core {


		PhysicsEngine::PhysicsEngine()
		{
		}

		void PhysicsEngine::simulate(float deltaTime)
		{
			for (size_t i = 0; i < m_PhysicsObjects.size(); i++)
			{
				m_PhysicsObjects[i]->integrate(deltaTime); 
			}
		}

		void PhysicsEngine::handleCollisions()
		{
			for (size_t i = 0; i < m_PhysicsObjects.size(); i++)
			{
				for (size_t j = i + 1; j <m_PhysicsObjects.size() ; j++)
				{
					IntersectData intersectData = m_PhysicsObjects[i]->getCollider().Intersect(
						m_PhysicsObjects[j]->getCollider());

					if (intersectData.getdoesIntersect())
					{

						if (m_PhysicsObjects[i]->getCollider().getType() == Collider::TYPE_PLANE && m_PhysicsObjects[j]->getCollider().getType() == Collider::TYPE_SPHERE)
						{
							
							vec3 normal = (static_cast<PlaneCollider*>(&m_PhysicsObjects[i]->getCollider()))->getNormal() ;
							float distance = (static_cast<PlaneCollider*>(&m_PhysicsObjects[i]->getCollider()))->getDistance(); 
						
							vec3  reflected = 2.0f * normal * (normal *m_PhysicsObjects[j]->getVelocity());
							
							vec3 prevVelocity = m_PhysicsObjects[j]->getVelocity(); 
							vec3 r2 = reflected; 
							r2.normalize(); 
							vec3 currVelocity = m_PhysicsObjects[j]->getVelocity() - reflected; //(reflected - r2 * 5.0f) ;
							float friction =0.0f; 
							if (prevVelocity.x != 0.0f || prevVelocity.z != 0.0f)
							{
								friction =0.4 * m_PhysicsObjects[j]->getMass() *0.098f;
							}
							m_PhysicsObjects[j]->setVelocity(m_PhysicsObjects[j]->getVelocity() - (reflected - reflected * 0.2f));
						

							if (currVelocity.y<1.0f)
							{
							m_PhysicsObjects[j]->m_CurrUseGravity = false; 
							}
						
					}
						else if (m_PhysicsObjects[j]->getCollider().getType() == Collider::TYPE_PLANE)
						{
								vec3 normal = (static_cast<PlaneCollider*>(&m_PhysicsObjects[i]->getCollider()))->getNormal();
								vec3  reflected = 2.0f * normal* (normal*m_PhysicsObjects[i]->getVelocity());
								m_PhysicsObjects[i]->setVelocity(m_PhysicsObjects[i]->getVelocity() - reflected);
						}

						//terrain and sphere detection collision
						if (m_PhysicsObjects[i]->getCollider().getType() == Collider::TYPE_TERRAIN
							&&
							m_PhysicsObjects[j]->getCollider().getType() == Collider::TYPE_SPHERE)
						{
							vec3 position = m_PhysicsObjects[j]->getPosition();
							float radius = (static_cast<SphereCollider*>(&m_PhysicsObjects[j]->getCollider())->getRadius());
							vec3 height = (static_cast<TerrainCollider*>(&m_PhysicsObjects[i]->getCollider()))->getTerrain().getHeightOfTerrain(position.x , position.z);
							m_PhysicsObjects[j]->getTransform()->move(vec3(0, height.y + radius,0)); 

							//vec3 position = m_PhysicsObjects[j]->getPosition(); 
							//vec3 normal = (static_cast<TerrainCollider*>(&m_PhysicsObjects[i]->getCollider()))->getTerrain().getNormal(position.x, position.z);
							////float distance = (static_cast<TerrainCollider*>(&m_PhysicsObjects[i]->getCollider()))->getDistance//();
							//
							//vec3  reflected = 2.0f * normal * (normal *m_PhysicsObjects[j]->getVelocity());
							//
							//vec3 prevVelocity = m_PhysicsObjects[j]->getVelocity();
							//vec3 r2 = reflected;
							//r2.normalize();
							//vec3 currVelocity = m_PhysicsObjects[j]->getVelocity() - reflected; //(reflected - r2 * 5.0f) ;
							//float friction = 0.0f;
							//if (prevVelocity.x != 0.0f || prevVelocity.z != 0.0f)
							//{
							//	friction = 0.4 * m_PhysicsObjects[j]->getMass() *0.098f;
							//}
							//m_PhysicsObjects[j]->setVelocity(m_PhysicsObjects[j]->getVelocity() - (reflected - reflected * 0.2f));
							//
							//
							//if (currVelocity.y < 1.0f)
							//{
							//	m_PhysicsObjects[j]->m_CurrUseGravity = false;
							//}
						}
						
						if (m_PhysicsObjects[i]->getCollider().getType() == Collider::TYPE_AABB && 
							m_PhysicsObjects[j]->getCollider().getType() == Collider::TYPE_SPHERE) {
							//std::cout << "AABB and the ball collided" << std::endl; 
							m_PhysicsObjects[j]->getTransform()->move(intersectData.getDistance() * intersectData.getDirection()); 

						}

						//do it for opposite and also for sphere Collider
					}
				}
			}
		}


		void PhysicsEngine::addPhysicsObject( PhysicsObject* physicsObject)
		{
			m_PhysicsObjects.push_back(physicsObject);
		}

		PhysicsEngine & PhysicsEngine::Instance()
		{
			//static object only initialized once same instance is returned.
			static PhysicsEngine* physicsEngine = new PhysicsEngine(); 
			return *physicsEngine; 
		}

		void PhysicsEngine::update(float deltaTime)
		{
			simulate(deltaTime); 
			handleCollisions(); 
		}
		

	}
}