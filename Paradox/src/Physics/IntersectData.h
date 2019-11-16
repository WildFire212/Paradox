#pragma once
#include"../maths/maths.h"
using namespace Paradox::maths; 
namespace Paradox {
	namespace physics {

		class IntersectData
		{
		private:

		public:
			explicit IntersectData(bool doesIntersect , vec3 direction,float distance) {
				m_DoesIntersect = doesIntersect; 
				m_Direction = direction;
				m_Distance = distance; 
			}

			~IntersectData() = default;
			//only getters for this class 
			inline auto getdoesIntersect() const -> const bool {
				return m_DoesIntersect; 

			}
			inline auto getDirection() const -> const vec3 {
				return m_Direction;
			}
			inline auto getDistance() const ->const float {
				return m_Distance;
			}
private: 
	vec3 m_Direction;
	float m_Distance;

	bool m_DoesIntersect;

};

} }
