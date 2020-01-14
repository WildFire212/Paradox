#pragma once
#ifndef CUBEMAP_H
#define CUBEMAP_H
#include"../../stb_image.h"
#include<GL/glew.h>
#include<string>
#include<vector>
namespace Paradox {
	namespace graphics {

		class CubeMap {
		private: 
			GLuint m_CubeMap; 
		public: 
			CubeMap(std::vector<std::string> faceLocations); 
			auto inline getCubeMap()->GLuint {
				return m_CubeMap; 
			}
			~CubeMap() {}
		private: 
			CubeMap():
			m_CubeMap(0){
			
			}
			

		};

	}
}
#endif