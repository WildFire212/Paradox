#pragma once

#include"vec3.h"
#include<glm.hpp>
#include"mat4.h"
#include<cmath>
namespace Paradox {
	namespace maths {

struct quaternion
{
	float x,y,z,w; 
	quaternion(); 
	quaternion(float x, float y ,float z, float w);
	quaternion(maths::vec3  axis, float angle);
	auto length() -> float; 

	void  normalize();
	void conjugate(); 
	auto Multiply(float r) -> quaternion&; 
	auto Multiply(const quaternion& other) -> quaternion&; 
	auto Multiply(maths::vec3 r) -> quaternion&; 
	auto Subtract(const quaternion& other) -> quaternion&; 
	auto Add(const quaternion& other) -> quaternion&; 
	auto toRotationMatrix() -> mat4;
	auto dot(quaternion r) -> float; 
	auto Nlerp(quaternion& dest, float lerpFactor, bool shortest) -> quaternion;
	auto Slerp(quaternion& dest, float lerpFactor, bool shortest) -> quaternion;
	~quaternion();

	friend auto operator*(quaternion left, const quaternion& right)->quaternion; 
	friend auto operator+(quaternion left, const quaternion& right)->quaternion; 
	friend auto operator-(quaternion left, const quaternion& right)->quaternion; 
	friend auto operator/(quaternion left, const quaternion& right)->quaternion; 
	
	auto operator==(const quaternion& other) -> bool; 
	auto operator!=(const quaternion& other) -> bool; 


	static auto nlerp(quaternion a, quaternion b, float blend) -> quaternion
	{
		//cout << a.w + a.x + a.y + a.z << endl;
		a.normalize();
		b.normalize();

		quaternion result;
		float dot_product = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		float one_minus_blend = 1.0F - blend;

		if (dot_product < 0.0F)
		{
			result.x = a.x * one_minus_blend + blend * -b.x;
			result.y = a.y * one_minus_blend + blend * -b.y;
			result.z = a.z * one_minus_blend + blend * -b.z;
			result.w = a.w * one_minus_blend + blend * -b.w;
		}
		else
		{
			result.x = a.x * one_minus_blend + blend * b.x;
			result.y = a.y * one_minus_blend + blend * b.y;
			result.z = a.z * one_minus_blend + blend * b.z;
			result.w = a.w * one_minus_blend + blend * b.w;
		}

		result.normalize();
		return result; 
	}

};
} }

