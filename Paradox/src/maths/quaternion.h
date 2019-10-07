#pragma once

#include"vec3.h"
#include<glm.hpp>
#include"mat4.h"
#include<math.h>
namespace Paradox {
	namespace maths {

struct quaternion
{
	float x,y,z,w; 
	quaternion(); 
	quaternion(float x, float y ,float z, float w);
	quaternion(maths::vec3  axis, float angle);
	float length(); 

	void  normalize();
	void conjugate(); 
	quaternion& Multiply(float r); 
	quaternion& Multiply(const quaternion& other); 
	quaternion& Multiply(maths::vec3 r); 
	quaternion& Subtract(const quaternion& other); 
	quaternion& Add(const quaternion& other); 
	mat4 toRotationMatrix();
	float dot(quaternion r); 
	quaternion Nlerp(quaternion& dest, float lerpFactor, bool shortest);
	quaternion Slerp(quaternion& dest, float lerpFactor, bool shortest);
	~quaternion();


	bool operator==(const quaternion& other); 
	bool operator!=(const quaternion& other); 


	static quaternion nlerp(quaternion a, quaternion b, float blend)
	{
		//cout << a.w + a.x + a.y + a.z << endl;
		a.normalize();
		b.normalize();

		quaternion result;
		float dot_product = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		float one_minus_blend = 1.0f - blend;

		if (dot_product < 0.0f)
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

