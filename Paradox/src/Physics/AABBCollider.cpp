#include "AABBCollider.h"
#include<math.h>
#include"SphereCollider.h"
namespace Paradox {
	namespace physics {



		AABBCollider::~AABBCollider()
		{
		}
		AABBCollider::AABBCollider(vec3 minBounds, vec3 maxBounds) : Collider(TYPE_AABB)
		{

			m_MaxBounds = maxBounds;
			m_MinBounds = minBounds;
			m_Directions = new vec3[4]{
				//vec3(0,1.0f,0.0f),
				//vec3(0,-1.0f,0.0f),
				vec3(1.0f,0.0f,0.0f),
				vec3(-1.0f,0.0,0.0f),
				vec3(0.0f,0.0,1.0f),
				vec3(0.0f,0.0,-1.0f),

			};
		}
		IntersectData AABBCollider::intersectAABB(const AABBCollider& other)
		{
			vec3 distances1 = m_MinBounds - other.getMaxBounds();
			vec3 distances2 = other.getMinBounds() - m_MaxBounds;

			vec3 distances = distances1.Max(distances2);

			float maxDistance = distances.Max();

			return IntersectData(maxDistance < 0,vec3(0,0,0), maxDistance);
		}
		double AABBCollider::squaredDistPointAABB(const vec3& point, const AABBCollider& aabb)
		{
			auto check = [&]
			(const float  pn,
				const float bmin,
				const float bmax)->float
			{
				float out = 0;
				float v = pn;
				float halfDist = (bmax - bmin)/2.0f; 

				if (v < bmin || v < halfDist)
				{
					float val = (bmin - v);
					out += val * val;

				}
				if (v > bmax || v > halfDist)
				{
					float val = (v- bmax);
					out += val * val;

				}
			
				return out;
			};
			float sq = 0.0; 

			sq += check(point.x, aabb.getMinBounds().x, aabb.getMaxBounds().x);
			sq += check(point.y, aabb.getMinBounds().y, aabb.getMaxBounds().y);
			sq += check(point.z, aabb.getMinBounds().z, aabb.getMaxBounds().z);
			return sq;
		}

		vec3 AABBCollider::closestPointOnAABB(const vec3& point) const
		{
			//auto check = [&]
			//(const float  pn,
			//	const float bmin,
			//	const float bmax)->float
			//{
			//	float out = 0;
			//	float v = pn;
			//	float halfDist = (bmax - bmin) / 2.0f;

			//	if (v < bmin|| v < halfDist)
			//	{
			//		out = bmin; 

			//	}
			//	if (v > bmax || v > halfDist)
			//	{
			//		out = bmax; 

			//	}
			//

			//	return out;
			//};

			//vec3 closestPoint; 

			//closestPoint.x= check(point.x, this->getMinBounds().x, this->getMaxBounds().x);
			////closestPoint.y= check(point.y,this->getMinBounds().y,this->getMaxBounds().y);
			//closestPoint.y = point.y; 
			//closestPoint.z= check(point.z,this->getMinBounds().z,this->getMaxBounds().z);
			//return closestPoint; 
			vec3 center(point);
			// Calculate AABB info (center, half-extents)
			vec3 aabb_half_extents((getMaxBounds().x - getMinBounds().x) / 2.0f, (getMaxBounds().y - getMinBounds().y) / 2.0f, (getMaxBounds().z - getMinBounds().z) / 2.0f);
			vec3 aabb_center(getMinBounds().x + aabb_half_extents.x, getMinBounds().y + aabb_half_extents.y, getMinBounds().z + aabb_half_extents.z);
			// Get difference vector between both centers
			vec3 difference = center - aabb_center;
			
			glm::vec3 diff(difference.x, difference.y, difference.z);

			glm::vec3 clamp = glm::clamp(diff,-glm::vec3(aabb_half_extents.x,aabb_half_extents.y,aabb_half_extents.z) ,glm::vec3( aabb_half_extents.x,aabb_half_extents.y,aabb_half_extents.z));
			// Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
			vec3 clamped(clamp.x, clamp.y, clamp.z); 
			vec3 closest = aabb_center + clamped;
			return closest; 
		}

		AABBCollider::Direction AABBCollider::vectorDirection(const SphereCollider& other) const
		{
			
			vec3 target; 
			//if (other.getCenter().x > getMinBounds().x&& other.getCenter().x < getMaxBounds().x &&
			//	other.getCenter().y > getMinBounds().y&& other.getCenter().y < getMaxBounds().y &&
			//	other.getCenter().z > getMinBounds().z&& other.getCenter().z < getMaxBounds().z)
			//{
			//target = closestPointOnAABB(other.getCenter()) - other.getCenter();
			//}
			//else {
			//
			//target=  other.getCenter() - closestPointOnAABB(other.getCenter()) ;
				//target.z =  other.getCenter().z- closestPointOnAABB(other.getCenter()).z;
			//}
			//target = other.getCenter(); 
			target = other.getCenter(); 
			// Calculate AABB info (center, half-extents)
			vec3 aabb_half_extents((getMaxBounds().x - getMinBounds().x) / 2.0f, (getMaxBounds().y - getMinBounds().y) / 2.0f, (getMaxBounds().z - getMinBounds().z) / 2.0f);
			vec3 aabb_center(getMinBounds().x + aabb_half_extents.x, getMinBounds().y + aabb_half_extents.y, getMinBounds().z + aabb_half_extents.z);
			// Get difference vector between both centers
			vec3 difference = target - aabb_center;

			int bestmatch = -1;
			float max = -1000.0f; 

			
			for (int i = 0; i < sizeof(m_Directions); i++)
			{
				difference.normalize(); 
				float dot = difference.dot(m_Directions[i]);
			//	dot = abs(dot);
				if (dot > max) {
					max = dot; 
					bestmatch = i; 
				}
			}
			return (Direction)bestmatch; 
		}

		IntersectData AABBCollider::intersectSphereCollider(const SphereCollider& other)
		{
			//std::cout << "collsion happened" << std::endl;
			float squaredDistance = squaredDistPointAABB(other.getCenter(), *this);
			vec3 closest = closestPointOnAABB(other.getCenter()); 
			vec3 V = closest - other.getCenter(); 

			float penetrationDistance = other.getRadius() - V.length(); 
			bool flag; 
			if (other.getCenter().x  + other.getRadius()> getMinBounds().x&& other.getCenter().x - other.getRadius() < getMaxBounds().x &&
				other.getCenter().y+ other.getRadius() > getMinBounds().y&& other.getCenter().y - other.getRadius() < getMaxBounds().y &&
				other.getCenter().z + other.getRadius() > getMinBounds().z&& other.getCenter().z - other.getRadius() < getMaxBounds().z)
			{
				flag= true; 
				//std::cout << "collsion aabb sphere closestPoint dd                           " << closest.x << "  "  <<closest.y<<" "<<closest.z << std::endl;
				//std::cout << "penetration Distance is" << penetrationDistance << std::endl; 
				//std::cout << "Direction is" << vectorDirection(other)<< std::endl; 
				
				
				return IntersectData(flag,m_Directions[vectorDirection(other)], penetrationDistance);
			}
			
				return IntersectData(false , vec3(0,0,0),-1000); 
			
			//If not, then return false

		}

		void AABBCollider::transform(const vec3& translation)
		{
			m_MinBounds += translation; 
			m_MaxBounds+= translation; 
		}



		}
	}
