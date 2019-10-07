#pragma once
#include"../maths/maths.h"
using namespace Paradox::maths; 
namespace Paradox {
	namespace physics {

		class IntersectData
		{
		private:

		public:
			explicit IntersectData(bool doesIntersect , vec3 direction) {
				m_DoesIntersect = doesIntersect; 
				m_Direction = direction; 
			}

			~IntersectData() {}
			//only getters for this class 
			inline const bool getdoesIntersect() const {
				return m_DoesIntersect; 

			}
			inline const vec3 getDirection() const {
				return m_Direction;
			}
private: 
	vec3 m_Direction;
	bool m_DoesIntersect;

};

} }
