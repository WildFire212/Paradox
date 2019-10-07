#include"vec3.h"

namespace Paradox {
	namespace maths {

		vec3::vec3() : x(0), y(0),z(0)
		{
		}

		vec3::vec3(float x, float y, float z)
		{
			this->x = x; 
			this->y = y; 
			this->z = z; 
		}

		vec3::vec3(float x)
		{
			this->x = x;
			this->y = x;
			this->z = x;

		}

		float vec3::length()
		{
			return sqrt((this->x* this->x) + (this->y* this->y) + (this->z* this->z));
		}

		void vec3::normalize()
		{
			this->x = this->x / this->length();
			this->y = this->y / this->length();
			this->z = this->z / this->length();
		}

		vec3 vec3::cross(const vec3& other)
		{
			vec3 Result; 
			Result.x = this->y*other.z - this->z* other.y;
			Result.y = this->z*other.x - this->x* other.z;
			Result.z = this->x* other.y - this->y* other.x;
			return Result; 
		}

		float vec3::dot(const vec3 & other)
		{
			return float(this->x  * other.x + this->y * other.y + this->z * other.z);
		}

		vec3 vec3::Max(const vec3 & other)
		{
			vec3 result = 0.0f; 
			result.x = x > other.x ? x : other.x; 
			result.y = y > other.y ? y : other.y;
			result.z = z > other.z ? z : other.z;
			return result; 
		}

		float vec3::Max()
		{
			float max = x; 
			if (x > y && x > z)
				max = x; 
			 if (y > x && y > z)
				max = y; 
			if (z > x && z > y)
				max =  z; 
			return max; 
		}

		vec3 vec3::reflect(vec3 normal)
		{
			return *this - (normal * (this->dot(normal) * 2.0f));	
		}

	

		vec3& vec3::Add(const vec3& other) {
			this->x += other.x; 
			this->y += other.y; 
			this->z += other.z; 
			return *this; 
		}

		vec3& vec3::Subtract(const vec3& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this; 
		}
		vec3& vec3::Multiply(const vec3& other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this; 
		}
		vec3& vec3::Divide(const vec3& other) {
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			return *this; 
		}
		//dont return references of local objects (therefore dont keep the return type as reference)
		vec3 operator+(vec3 left, const vec3& right) {
			return left.Add(right);	
		}
		vec3 operator-(vec3 left, const vec3& right) {
			return left.Subtract(right); 
		}
		vec3 operator*(vec3 left, const vec3& right) {
			return left.Multiply(right); 
		}
		vec3 operator/(vec3 left, const vec3& right) {
			return left.Divide(right); 
		}
		vec3 operator+(vec3 left, float right)
		{
			return vec3(left.x + right, left.y + right, left.z + right); 
		}
		vec3 operator-(vec3 left, float right)
		{
			return  vec3(left.x - right, left.y - right, left.z - right);
		}
		vec3 operator*(vec3 left, float right)
		{
			return  vec3(left.x * right, left.y * right, left.z * right);
		}
		vec3 operator/(vec3 left, float right)
		{
			return  vec3(left.x / right, left.y / right, left.z / right);
		}
		vec3 vec3::operator+=(vec3 right)
		{
			(*this) = (*this) + right; 
			return *this; 
		}
		vec3 vec3::operator-=(vec3 right)
		{
			(*this) = (*this) - right;
			return *this;
		}
		bool vec3::operator== (const vec3& other) const {
			return (x == other.x && y == other.y && z == other.z);
		}
		bool vec3::operator!= (const vec3& other) const {
			return !(*this == other); 
		}
} }
