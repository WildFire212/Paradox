#pragma once

#include"vec4.h"
#include"vec3.h"
#include<cmath>
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

			auto getColumn(int colIndex) -> vec4;
			static auto Identity() -> mat4; 

			auto Multiply(const mat4& other) -> mat4&;
			auto Add(const mat4& other) -> mat4&; 
			auto Subtract(const mat4& other) -> mat4&; 
			//overloaded operators 

			friend auto operator*(mat4 left, const mat4& right) -> mat4;
			friend auto operator+(mat4 left, const mat4& right) -> mat4;
			friend auto operator-(mat4 left, const mat4& right) -> mat4;
			
			auto operator!=(const mat4& other)	const -> bool; 
			auto operator==(const mat4& other) const -> bool; 
			//bool operator!=(nullptr_t) const; 
			static auto Orthographic(float left, float right, float bottom, float top, float near, float far) -> mat4;
			static auto Perpective(float fov, float aspectRatio, float near, float far) -> mat4;

			static auto Translate(const vec3& translation) -> mat4;
			static auto Rotate(vec3 forward, vec3 up, vec3 right) -> mat4;
			static auto Rotate(quaternion quat) -> mat4;
			static auto Rotate(vec3 forward, vec3 up) -> mat4; 
			static auto Rotate(float angle, const vec3& axis) -> mat4;
			//static auto Rotate(const quaternion& quat) ->mat4; 
			static auto Scale(const vec3& scale) -> mat4;
			static auto Scale(float x, float y, float z) -> mat4; 
			static auto aIMatrix4x4ToMat4(aiMatrix4x4 matrix) -> mat4;
		};
} }