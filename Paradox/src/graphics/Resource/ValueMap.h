#pragma once
#include<map>
#include<string>
#include"../../maths/maths.h"
#include<GL/glew.h>
namespace Paradox {
	namespace graphics {

		class ValueMap {
		private: 
			std::map < std::string, maths::vec3 > m_Vector3Map; 
			std::map < std::string, GLfloat> m_FloatMap;

		public : 
			ValueMap() {}
			~ValueMap() {}
			void addVector3(std::string valueName, maths::vec3 value)
			{
				m_Vector3Map[valueName] = value; 
			}
			void addFloat(std::string valueName, GLfloat value) {
				m_FloatMap[valueName] = value; 
			}
			GLfloat getFloat(std::string valueName) const {
				auto search = m_FloatMap.find(valueName);
				if (search != m_FloatMap.end()) {
					return search->second;
				}
				else {
					return 0.0f;
				}
			}
			maths::vec3 getVector3(std::string valueName)	const {
				auto search = m_Vector3Map.find(valueName);
				if (search != m_Vector3Map.end()) {
					return search->second;
				}
				else {
					return maths::vec3(0.0f, 0.0f, 0.0f);
				}
			}

		};


} }