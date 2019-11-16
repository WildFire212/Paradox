
#include "quaternion.h"

namespace Paradox {
	namespace maths {


quaternion::quaternion()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}


quaternion::quaternion(float x, float y, float z, float w)
{
	this->x = x; 
	this->y = y; 
	this->z = z;
	this->w = w; 
}

quaternion::quaternion(maths::vec3 axis, float angle)
{

	float sinHalfAngle = (float)glm::sin(angle / 2);
	float cosHalfAngle = (float)glm::cos(angle / 2);

	this->x = axis.x * sinHalfAngle; 
	this->y = axis.y * sinHalfAngle;
	this->z = axis.z * sinHalfAngle;
	this->w = cosHalfAngle; 

}

float quaternion::length()
{
	return (float)sqrt(x * x + y * y + z * z + w * w); 
}

void quaternion::normalize()
{
	this->x = this->x / this->length();
	this->y = this->y / this->length();
	this->z = this->z / this->length();
	this->w = this->w / this->length();
}

void quaternion::conjugate()
{
	this->x = -this->x ;
	this->y =-this->y ;
	this->z =-this->z ;
	this->w =this->w ;
}

quaternion & quaternion::Multiply(float r)
{
	// TODO: insert return statement here
	this->x *=r; 
	this->y *=r; 
	this->z *=r; 
	this->w *=r; 
	return *this;

	
}

quaternion & quaternion::Multiply(const quaternion & other)
{
	// TODO: insert return statement here
	this->w = this->w * other.w - this->x * other.x - this->y* other.y - this->z * other.z; 
	this->y = this->x * other.w + this->w * other.x + this->y* other.z - this->z * other.y;
	this->z = this->y * other.w + this->w * other.y + this->z* other.x - this->x * other.z;
	this->z = this->z * other.w + this->w * other.z + this->x* other.y - this->y * other.x;
	return *this;
}

quaternion & quaternion::Multiply(maths::vec3 r)
{
	// TODO: insert return statement here
	this->w = -this->x * r.x - this->y * r.y - this->z * r.z;
	this->x =  this->w * r.x + this->y * r.z - this->z * r.y;
	this->y =  this->w * r.y + this->z * r.x - this->x * r.z;
	this->z =  this->w * r.z + this->x * r.y - this->y * r.x;
	return *this; 
}

quaternion & quaternion::Subtract(const quaternion & other)
{
	// TODO: insert return statement here
	this->x -= other.x; 
	this->y -= other.y; 
	this->z -= other.z; 
	this->w -= other.w; 
	return *this; 
}

quaternion & quaternion::Add(const quaternion & other)
{
	// TODO: insert return statement here
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
	return *this;
}

mat4 quaternion::toRotationMatrix()
{
	vec3 forward =vec3(2.0f * (this->x * this->z - this->w * this->y), 2.0f * (this->y * this->z + this->w * this->x), 1.0f - 2.0f * (this->x * this->x + this->y * this->y));
	vec3 up =    vec3(2.0f * (this->x * this->y + this->w * this->z), 1.0f - 2.0f * (this->x * this->x + this->z * this->z), 2.0f * (this->y * this->z - this->w * this->x));
	vec3 right = vec3(1.0f - 2.0f * (this->y * this->y + this->z * this->z), 2.0f * (this->x * this->y - this->w * this->z), 2.0f * (this->x * this->z + this->w * this->y));

	return mat4::Rotate(forward, up, right);
}


float quaternion::dot(quaternion other)
{
	return (this->x * other.x + this->y * other.y + this->z  * other.z + this->w * other.w); 
}

quaternion quaternion::Nlerp(quaternion& dest, float lerpFactor, bool shortest)
{
	quaternion corrDest = dest; 
	if (shortest && this->dot(dest) < 0)
	{
		corrDest = quaternion(-dest.x, -dest.y, -dest.z,-dest.w); 

	}

	corrDest.Subtract(*this).Multiply(lerpFactor).Add(*this);
	corrDest.normalize(); 
	return corrDest; 
}

quaternion quaternion::Slerp(quaternion& dest, float lerpFactor, bool shortest) {
	const float epsilon = 1e3f;

	float cos = this->dot(dest);
	quaternion corrDest = dest; 

	if (shortest && cos < 0) {
		cos = -cos; 
		corrDest = quaternion(-dest.x, -dest.y, -dest.z,-dest.w); 
	}
	if (glm::abs(cos) >= 1 - epsilon)
	{
		return Nlerp(corrDest, lerpFactor, false);
	}


	float sin = (float)glm::sqrt(1.0f - cos * cos); 
	float angle = (float)atan2(sin, cos); 
	float invSin = 1.0f / sin; 

	float srcFactor = (float)glm::sin(1.0f - lerpFactor) * angle * invSin; 
	float destFactor = (float)glm::sin((lerpFactor)* angle) * invSin; 

	return this->Multiply(srcFactor).Add(corrDest.Multiply(destFactor));
}
quaternion::~quaternion()
{
}
bool quaternion::operator==(const quaternion & other)
{
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}
bool quaternion::operator!=(const quaternion & other)
{
	return !(*this == other); 
}
}
auto maths::operator*(quaternion left, const quaternion& right) -> quaternion
{
	return left.Multiply(right); 
	
}
auto maths::operator+(quaternion left, const quaternion& right) -> quaternion
{
	return left.Add(right);
}
auto maths::operator-(quaternion left, const quaternion& right) -> quaternion
{
	return left.Subtract(right);
}
auto maths::operator/(quaternion left, const quaternion& right) -> quaternion
{
	return quaternion(); 
}
}
