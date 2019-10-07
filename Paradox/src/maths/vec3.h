#pragma once
#include<math.h>
namespace Paradox {
	namespace maths {

		struct vec3 {
			float x, y ,z;
			vec3() ; 
			vec3(float x, float y,float z);
			vec3(float x); 
			float length(); 
			void normalize();
			vec3 cross(const vec3& other); 
			float dot(const vec3& other); 
			vec3 Max(const vec3& other); 
			float Max(); 
			vec3 reflect(vec3 normal); 
			vec3& Add(const vec3& other);	//return by reference because 
			vec3& Subtract(const vec3& other);	
			vec3& Multiply(const vec3& other);
			vec3& Divide(const vec3& other);
			
			friend vec3 operator+(vec3 left, const vec3& right);
			friend vec3 operator-(vec3 left, const vec3& right);
			friend vec3 operator*(vec3 left, const vec3& right);
			friend vec3 operator/(vec3 left, const vec3& right);

			friend vec3 operator+(vec3 left, float right);
			friend vec3 operator-(vec3 left, float right);
			friend vec3 operator*(vec3 left, float right);
			friend vec3 operator/(vec3 left, float right);
			

			vec3 operator+=(vec3 right);
			vec3 operator-=(vec3 right);

			bool operator==(const vec3& other) const; 
			bool operator!= (const vec3& other) const; 
		};

} }
