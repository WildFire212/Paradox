#pragma once
#include<string>
#include"../../../maths/maths.h"
namespace Paradox {
	namespace graphics {

		class Bone {
		public:
			std::string m_Name;
			maths::mat4 m_FinalTransformation;
			maths::mat4 m_OffsetMatrix;


		};
	}
}