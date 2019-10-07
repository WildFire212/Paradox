#pragma once

namespace Paradox {
	namespace maths {

		struct vec4 {
			float x, y,z,w;
			vec4();
			vec4(float x, float y, float z, float w);
			
			
			constexpr vec4& Add(const vec4& other);	//return by reference because 
			constexpr vec4& Subtract(const vec4& other);
			vec4& Multiply(const vec4& other);
			vec4& Divide(const vec4& other);
			
			friend vec4 operator+(vec4 left, const vec4& right);
			friend vec4 operator-(vec4 left, const vec4& right);
			friend vec4 operator*(vec4 left, const vec4& right);
			friend vec4 operator/(vec4 left, const vec4& right);
			
			bool operator==(const vec4& other) const; 
			bool operator!= (const vec4& other) const; 
		};

} }
