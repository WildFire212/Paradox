#pragma once

#include"vec4.h"
#include"vec3.h"
#include<math.h>
#include<assimp/matrix4x4.h>
#include<glm.hpp>

#define SIZE 4*4
namespace Paradox {
	namespace maths {
		class quaternion; 
		struct mat4 {
			//opengl uses col major ordering therefore 
			//[row + col * 4 ]
			union {
				float elements[SIZE];
				vec4 columns[4];
			};
			mat4(); 
			mat4(float diagonal);
			mat4(float* elements);
			mat4(const vec4& row0, const vec4& row1, const vec4& row2, const vec4& row3);

			vec4 getColumn(int colIndex);
			static mat4 Identity(); 

			mat4& Multiply(const mat4& other);
			mat4& Add(const mat4& other); 
			mat4& Subtract(const mat4& other); 
			//overloaded operators 

			friend mat4 operator*(mat4 left, const mat4& right);
			friend mat4 operator+(mat4 left, const mat4& right);
			friend mat4 operator-(mat4 left, const mat4& right);
			
			bool operator!=(const mat4& other)	const; 
			bool operator==(const mat4& other) const; 
			//bool operator!=(nullptr_t) const; 
			static mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 Perpective(float fov, float aspectRatio, float near, float far);

			static mat4 Translate(const vec3& translation);
			static mat4 Rotate(vec3 forward, vec3 up, vec3 right);
			static mat4 Rotate(quaternion quat);
			static mat4 Rotate(vec3 forward, vec3 up); 
			static mat4 Rotate(float angle, const vec3& axis);
			static mat4 Scale(const vec3& scale);
			static mat4 Scale(float x, float y, float z); 
			static mat4 aIMatrix4x4ToMat4(aiMatrix4x4 matrix);
		};
} }