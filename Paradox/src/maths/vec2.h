#pragma once

namespace Paradox {
	namespace maths {

		struct vec2 {
			float x, y;
			vec2();
			vec2(float x);
			vec2(float x, float y);
			
			
			vec2& Add(const vec2& other);	//return by reference because 
			vec2& Subtract(const vec2& other);
			vec2& Multiply(const vec2& other);
			vec2& Divide(const vec2& other);
			
			friend vec2 operator+(vec2 left, const vec2& right);
			friend vec2 operator-(vec2 left, const vec2& right);
			friend vec2 operator*(vec2 left, const vec2& right);
			friend vec2 operator/(vec2 left, const vec2& right);
			
			bool operator==(const vec2& other) const; 
			bool operator!= (const vec2& other) const; 
		};

} }
