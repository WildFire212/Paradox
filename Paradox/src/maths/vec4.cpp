#include"vec4.h"

namespace Paradox {
	namespace maths {

		vec4::vec4() : x(0), y(0)
		{
		}

		vec4::vec4(float x, float y, float z, float w)
		{
			this->x = x; 
			this->y = y; 
			this->z = z; 
			this->w = w; 
		}

		constexpr vec4& vec4::Add(const vec4& other) {
			this->x += other.x; 
			this->y += other.y; 
			this->z += other.z; 
			this->w += other.w; 
			return *this; 
		}

		constexpr vec4& vec4::Subtract(const vec4& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;
			return *this; 
		}
		vec4& vec4::Multiply(const vec4& other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			this->w *= other.w;
			return *this; 
		}
		vec4& vec4::Divide(const vec4& other) {
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			this->w /= other.w;
			return *this; 
		}
		//dont return references of local objects (therefore dont keep the return type as reference)
		vec4 operator+(vec4 left, const vec4& right) {
			return left.Add(right);	
		}
		vec4 operator-(vec4 left, const vec4& right) {
			return left.Subtract(right); 
		}
		vec4 operator*(vec4 left, const vec4& right) {
			return left.Multiply(right); 
		}
		vec4 operator/(vec4 left, const vec4& right) {
			return left.Divide(right); 
		}
		bool vec4::operator== (const vec4& other) const {
			return (x == other.x && y == other.y && z == other.z && w == other.w);
		}
		bool vec4::operator!= (const vec4& other) const {
			return !(*this == other); 
		}
} }



