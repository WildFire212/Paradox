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
			ValueMap() = default;
			~ValueMap() = default;
			void addVector3(std::string valueName, maths::vec3 value)
			{
				m_Vector3Map[valueName] = value; 
			}
			void addFloat(std::string valueName, GLfloat value) {
				m_FloatMap[valueName] = value; 
			}
			auto getFloat(std::string valueName) const -> GLfloat {
				auto search = m_FloatMap.find(valueName);
				if (search != m_FloatMap.end()) {
					return search->second;
				}
				
					return 0.0F;
				
			}
			auto getVector3(std::string valueName)	const -> maths::vec3 {
				auto search = m_Vector3Map.find(valueName);
				if (search != m_Vector3Map.end()) {
					return search->second;
				}
				
					return {0.0F, 0.0F, 0.0F};
				
			}

		};


} }