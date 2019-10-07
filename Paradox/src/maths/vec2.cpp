#include"vec2.h"

namespace Paradox {
	namespace maths {

		vec2::vec2() : x(0), y(0)
		{
		}
		vec2::vec2(float x)
		{
			this->x = x;
			this->y = x;
		}
		vec2::vec2(float x, float y)
		{
			this->x = x; 
			this->y = y; 
		}

		vec2& vec2::Add(const vec2& other) {
			this->x += other.x; 
			this->y += other.y; 
			return *this; 
		}

		vec2& vec2::Subtract(const vec2& other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this; 
		}
		vec2& vec2::Multiply(const vec2& other) {
			this->x *= other.x;
			this->y *= other.y;
			return *this; 
		}
		vec2& vec2::Divide(const vec2& other) {
			this->x /= other.x;
			this->y /= other.y;
			return *this; 
		}
		//dont return references of local objects (therefore dont keep the return type as reference)
		vec2 operator+(vec2 left, const vec2& right) {
			return left.Add(right);	
		}
		vec2 operator-(vec2 left, const vec2& right) {
			return left.Subtract(right); 
		}
		vec2 operator*(vec2 left, const vec2& right) {
			return left.Multiply(right); 
		}
		vec2 operator/(vec2 left, const vec2& right) {
			return left.Divide(right); 
		}
		bool vec2::operator== (const vec2& other) const {
			return (x == other.x && y == other.y);
		}
		bool vec2::operator!= (const vec2& other) const {
			return !(*this == other); 
		}
} }
