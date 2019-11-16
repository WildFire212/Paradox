#pragma once

namespace Paradox {
	namespace maths {

		struct vec4 {
			float x, y,z,w;
			vec4();
			vec4(float x, float y, float z, float w);
			
			
			constexpr auto Add(const vec4& other) -> vec4&;	//return by reference because 
			constexpr auto Subtract(const vec4& other) -> vec4&;
			auto Multiply(const vec4& other) -> vec4&;
			auto Divide(const vec4& other) -> vec4&;
			
			friend auto operator+(vec4 left, const vec4& right) -> vec4;
			friend auto operator-(vec4 left, const vec4& right) -> vec4;
			friend auto operator*(vec4 left, const vec4& right) -> vec4;
			friend auto operator/(vec4 left, const vec4& right) -> vec4;
			
			auto operator==(const vec4& other) const -> bool; 
			auto operator!= (const vec4& other) const -> bool; 
		};

} }
