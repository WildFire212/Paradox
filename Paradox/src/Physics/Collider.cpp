#include "Collider.h"
#include"SphereCollider.h"
#include"PlaneCollider.h"
#include"TerrainCollider.h"
namespace Paradox {
	namespace physics {

 IntersectData Collider::Intersect(const Collider & other)
{
	try {
		if (this->getType() == TYPE_SPHERE && other.getType() == TYPE_SPHERE)
		{
			//casting to derived class to access derived class non virtual function

			SphereCollider* thisSphereCollider = (SphereCollider*)(this);

			return thisSphereCollider->intersectSphereCollider((SphereCollider&)other);
		}
		if (this->getType() ==	 TYPE_PLANE && other.getType() == TYPE_SPHERE)
		{
			PlaneCollider* thisPlaneCollider = (PlaneCollider*)(this); 
			return thisPlaneCollider->intersectSphereCollider((SphereCollider&)other); 
		}
		if (this->getType() == TYPE_TERRAIN && other.getType() == TYPE_SPHERE)
		{
			TerrainCollider* thisTerrainCollider = (TerrainCollider*)(this); 
			return thisTerrainCollider->intersectSphereCollider((SphereCollider&)other); 
		}
		else {
			throw std::runtime_error(" NO TEST FOR GIVEN COLLIDER TYPES");
		}
	}

	catch (std::runtime_error e)
	{
		std::cout << "Invalid Collider input : " << e.what() << std::endl;
	}
}
 void Collider::setPhysicsMaterial(const PhysicsMaterial* physicsMaterial)
 {
	 m_PhysicsMaterial = physicsMaterial;
 }

} }
