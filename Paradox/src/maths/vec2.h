#pragma once

namespace Paradox {
	namespace maths {

		struct vec2 {
			float x, y;
			vec2();
			vec2(float x);
			vec2(float x, float y);
			
			
			auto Add(const vec2& other) -> vec2&;	//return by reference because 
			auto Subtract(const vec2& other) -> vec2&;
			auto Multiply(const vec2& other) -> vec2&;
			auto Divide(const vec2& other) -> vec2&;
			
			friend auto operator+(vec2 left, const vec2& right) -> vec2;
			friend auto operator-(vec2 left, const vec2& right) -> vec2;
			friend auto operator*(vec2 left, const vec2& right) -> vec2;
			friend auto operator/(vec2 left, const vec2& right) -> vec2;
			
			auto operator==(const vec2& other) const -> bool; 
			auto operator!= (const vec2& other) const -> bool; 
		};

} }
