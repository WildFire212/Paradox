#pragma once
#include"../Components/Terrain.h"
#include"SphereCollider.h"
#include"../maths/maths.h"
using namespace Paradox::maths;
namespace Paradox {
	namespace physics {
		class TerrainCollider : public Collider
		{
		private: 
		   const Terrain&  m_Terrain; 
		public : 
			explicit TerrainCollider(const Terrain& terrain);
			
			//Intersect Data
			IntersectData intersectSphereCollider(const SphereCollider& sphereCollider);

			inline const Terrain& getTerrain() const {
				return m_Terrain; 
			}
			
		
		};
} }