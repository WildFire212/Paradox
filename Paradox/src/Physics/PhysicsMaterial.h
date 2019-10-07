#pragma once
namespace Paradox {
	namespace physics {
		class PhysicsMaterial {
		public : 
			PhysicsMaterial(float staticFriction , float dynamicFriction, float bounciness) {
				m_DynamicFriction = dynamicFriction;
				m_StaticFriction = staticFriction;
				m_Bounciness = bounciness;
			}
			float m_DynamicFriction; 
			float m_StaticFriction; 
			float m_Bounciness; 
		};
} }