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
			auto intersectSphereCollider(const SphereCollider& sphereCollider) -> IntersectData;

			inline auto getTerrain() const -> const Terrain& {
				return m_Terrain; 
			}
			
		
		};
} }