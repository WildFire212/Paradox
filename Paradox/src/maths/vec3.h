#pragma once
#include<cmath>
namespace Paradox {
	namespace maths {

		struct vec3 {
			float x, y ,z;
			vec3() ; 
			vec3(float x, float y,float z);
			vec3(float x); 
			auto length() -> float; 
			void normalize();
			auto cross(const vec3& other) -> vec3; 
			auto dot(const vec3& other) -> float; 
			auto Max(const vec3& other) -> vec3; 
			auto Max() -> float; 
			auto reflect(vec3 normal) -> vec3; 
			auto Add(const vec3& other) -> vec3&;	//return by reference because 
			auto Subtract(const vec3& other) -> vec3&;	
			auto Multiply(const vec3& other) -> vec3&;
			auto Divide(const vec3& other) -> vec3&;
			
			friend auto operator+(vec3 left, const vec3& right) -> vec3;
			friend auto operator-(vec3 left, const vec3& right) -> vec3;
			friend auto operator*(vec3 left, const vec3& right) -> vec3;
			friend auto operator/(vec3 left, const vec3& right) -> vec3;

			friend auto operator+(vec3 left, float right) -> vec3;
			friend auto operator-(vec3 left, float right) -> vec3;
			friend auto operator*(vec3 left, float right) -> vec3;
			friend auto operator/(vec3 left, float right) -> vec3;
			

			auto operator+=(vec3 right) -> vec3;
			auto operator-=(vec3 right) -> vec3;

			auto operator==(const vec3& other) const -> bool; 
			auto operator!= (const vec3& other) const -> bool; 
		};

} }
