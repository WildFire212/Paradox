#include"mat4.h"
#include<sstream>
#include<math.h>
#include"quaternion.h"
namespace Paradox {
	namespace maths {
		
		mat4::mat4()  {
			for (int i = 0; i < SIZE; i++)
			{
				elements[i] = 0; 
			}
	}
	
		mat4::mat4(float diagonal)
		{
			memset(elements, 0, SIZE *sizeof(float));

			elements[0 * 4 + 0] = diagonal;
			elements[1 * 4 + 1] = diagonal;
			elements[2 * 4 + 2] = diagonal;
			elements[3 * 4 + 3] = diagonal;
		}

		mat4::mat4(float* elements)
		{
			memcpy(this->elements, elements, sizeof(float) * SIZE);
		}

		mat4::mat4(const vec4& row0, const vec4& row1, const vec4& row2, const vec4& row3) {
		
		}

		vec4 mat4::getColumn(int colIndex) {
			return vec4(elements[0+ colIndex *4 ], elements[1 + colIndex * 4], elements[2 + colIndex * 4], elements[3 + colIndex * 4]);
		}

		mat4 mat4::Identity() {
			return mat4(1.0f);
		}

		mat4& mat4::Multiply(const mat4& other) {
			float data[16]; 
			for (size_t row = 0; row < 4; row++)
			{
				for (int32_t col = 0; col < 4; col++)
				{
					float sum = 0.0f; 
					for (int32_t e = 0; e < 4; e++)
					{
						sum += elements[e * 4 +row ] * other.elements[col * 4 + e ];
					}
					data[row + 4 * col ] = sum;
				}
			}
			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}

		mat4 & mat4::Add(const mat4 & other)
		{
			// TODO: insert return statement here
			for (size_t i = 0; i < SIZE; i++)
			{
				this->elements[i] = this->elements[i] + other.elements[i]; 
			}
			return *this; 
		}

		mat4 & mat4::Subtract(const mat4 & other)
		{
			// TODO: insert return statement here
			for (size_t i = 0; i < SIZE; i++)
			{
				this->elements[i] = this->elements[i] + other.elements[i];
			}
			return *this;

		}
		
		mat4 operator*(mat4 left, const mat4& right) {
			return left.Multiply(right);
		}

		mat4 operator+(mat4 left, const mat4 & right)
		{
			return left.Add(right); 
		}

		mat4 operator-(mat4 left, const mat4 & right)
		{
			return left.Subtract(right); 
		}
		
		bool mat4::operator!=(const mat4 & other) const
		{
			
			return !(*this == other);
		}

		bool mat4::operator==(const mat4 & other) const
		{
			for (size_t i = 0; i < SIZE; i++)
			{
				if (elements[i] != other.elements[i])
				{
					return false; 
				}

			}
			return true; 
		}
		
	//bool mat4::operator!=(nullptr_t) const
	//{
	//	return *this != mat4(0.0f); 
	//	//return *this!= (mat4)nullptr; 
	//}
	//
		mat4 mat4::Orthographic(float left, float right, float bottom, float top, float near, float far) {
			mat4 result(1.0f);
			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = -2.0f /	(far - near);
			result.elements[3 + 3 * 4] = 1.0f;
			
			result.elements[0 + 3 * 4] = -(right + left) / (right - left);
			result.elements[1 + 3 * 4] = -(top + bottom) / (top - bottom);
			result.elements[2 + 3 * 4] = - (far + near)/(far - near);
			
			return result; 
		}

		mat4 mat4::Perpective(float fov, float aspectRatio, float near, float far) {
			mat4 result(1.0f);
			
			float q =  tan(glm::radians(0.5f * fov));
			float a =(q *  aspectRatio); 

			float b = (near + far) / (far - near);
			float c = (2.0f * near * far) / (far - near);

			result.elements[0 + 0 * 4] = 1.0f/a; 
			result.elements[1 + 1 * 4] = 1.0f/q; 
			result.elements[2 + 2 * 4] = - b; 
			result.elements[2 + 3 * 4] = -c;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[3 + 3 * 4] = 0.0f;
			return result; 
		}

		mat4 mat4::Translate(const vec3& translation) {
			mat4 result(1.0f);

			result.elements[0+ 4 *  3] = translation.x;
			result.elements[1+ 4 *  3] = translation.y;
			result.elements[2+ 4 *  3] = translation.z;
			return result; 
		}

		mat4 mat4::Rotate(vec3 forward, vec3 up, vec3 right)
		{
			vec3 f = forward; 
			vec3 r = right; 
			vec3 u = up; 

			mat4 result(1.0);  
			result.elements[0 + 4 * 0] = r.x;	result.elements[0 + 4 * 1] = r.y;	result.elements[0 + 4 * 2] = r.z;	result.elements[0 + 4 * 3] = 0;
			result.elements[1 + 4 * 0] = u.x;	result.elements[1 + 4 * 1] = u.y;	result.elements[1 + 4 * 2] = u.z;	result.elements[1 + 4 * 3] = 0;
			result.elements[2 + 4 * 0] = f.x;	result.elements[2 + 4 * 1] = f.y;	result.elements[2 + 4 * 2] = f.z;	result.elements[2 + 4 * 3] = 0;
			result.elements[3 + 4 * 0] = 0;		result.elements[3 + 4 * 1] = 0;		result.elements[3 + 4 * 2] = 0;		result.elements[3 + 4 * 3] = 1;

				return result; 																												
		}

		mat4 mat4::Rotate(quaternion quat)
		{
			mat4 result = Identity();

			float qx, qy, qz, qw, qx2, qy2, qz2, qxqx2, qyqy2, qzqz2, qxqy2, qyqz2, qzqw2, qxqz2, qyqw2, qxqw2;
			qx = quat.x;
			qy = quat.y;
			qz = quat.z;
			qw = quat.w;
			qx2 = (qx + qx);
			qy2 = (qy + qy);
			qz2 = (qz + qz);
			qxqx2 = (qx * qx2);
			qxqy2 = (qx * qy2);
			qxqz2 = (qx * qz2);
			qxqw2 = (qw * qx2);
			qyqy2 = (qy * qy2);
			qyqz2 = (qy * qz2);
			qyqw2 = (qw * qy2);
			qzqz2 = (qz * qz2);
			qzqw2 = (qw * qz2);

			//result.rows[0] = vec4(((1.0f - qyqy2) - qzqz2), (qxqy2 - qzqw2), (qxqz2 + qyqw2), 0.0f);
			//result.rows[1] = vec4((qxqy2 + qzqw2), ((1.0f - qxqx2) - qzqz2), (qyqz2 - qxqw2), 0.0f);
			//result.rows[2] = vec4((qxqz2 - qyqw2), (qyqz2 + qxqw2), ((1.0f - qxqx2) - qyqy2), 0.0f);
			result.elements[0*  4 + 0] = ((1.0f - qyqy2) - qzqz2);	result.elements[1 * 4 + 0] = (qxqy2 - qzqw2);	result.elements[2 * 4+  0] = (qxqz2 + qyqw2);	result.elements[3 * 4 + 0] = 0.0f;
			result.elements[0*  4 + 1] = (qxqy2 + qzqw2);	result.elements[1  * 4 + 1] = ((1.0f - qxqx2) - qzqz2);	result.elements[2 * 4+  1] = (qyqz2 - qxqw2);	result.elements[3 * 4 + 1] = 0.0f;
			result.elements[0*  4 + 2] = (qxqz2 - qyqw2);	result.elements[1 * 4 + 2] = (qyqz2 + qxqw2);	result.elements[2*  4 +  2] = ((1.0f - qxqx2) - qyqy2);	result.elements[3 * 4 + 2] = 0.0f;
			result.elements[3*  4 + 0] = 0;		result.elements[3 * 4 + 1] = 0;		result.elements[3 * 4 + 2] = 0;		result.elements[3 * 4 + 3] = 1.0f;

			return result;
		}

		mat4 mat4::Rotate(vec3 forward, vec3 up)
		{
			forward.normalize(); 
			up.normalize(); 

			vec3 r = up.cross(forward);

			vec3 u = forward.cross(r); 
			return Rotate(forward, u, r); 
		}

		mat4 mat4::Rotate(float angle, const vec3& axis) {
			
			mat4 result(1.0f);
			
			float r = 2;// toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c; 

			float x = axis.x; 
			float y = axis.y; 
			float z = axis.z; 

			result.elements[0 + 0 * 4] = x * x* omc + c; 
			result.elements[0 + 1 * 4] = y * x* omc +z  * s; 
			result.elements[0 + 2 * 4] = x * z* omc  - y * s; 
			
			result.elements[1 + 0 * 4] = x * y* omc - z  * s; 
			result.elements[1 + 1 * 4] = y * y* omc + c; 
			result.elements[1 + 2 * 4] = y * z * omc + x * s; 
			
			result.elements[2 + 0 * 4] = x * z * omc + y * s; 
			result.elements[2 + 1 * 4] = y * z* omc - x * s; 
			result.elements[2 + 2 * 4] = z * z* omc +c; 
			
			return result; 

		}

	/*	auto mat4::Rotate(const quaternion& quat) -> mat4
		{
			mat4 result = Identity();

			float qx, qy, qz, qw, qx2, qy2, qz2, qxqx2, qyqy2, qzqz2, qxqy2, qyqz2, qzqw2, qxqz2, qyqw2, qxqw2;
			qx = quat.x;
			qy = quat.y;
			qz = quat.z;
			qw = quat.w;
			qx2 = (qx + qx);
			qy2 = (qy + qy);
			qz2 = (qz + qz);
			qxqx2 = (qx * qx2);
			qxqy2 = (qx * qy2);
			qxqz2 = (qx * qz2);
			qxqw2 = (qw * qx2);
			qyqy2 = (qy * qy2);
			qyqz2 = (qy * qz2);
			qyqw2 = (qw * qy2);
			qzqz2 = (qz * qz2);
			qzqw2 = (qw * qz2);

			result.elements[0 + 0 * 4] = ((1.0f - qyqy2) - qzqz2); result.elements[0 + 1* 4] =(qxqy2 - qzqw2)				; result.elements[0 + 2 * 4] = (qxqz2 + qyqw2);
			result.elements[1 + 0 * 4] = (qxqy2 + qzqw2);		   result.elements[1 + 1 * 4]= ((1.0f - qxqx2) - qzqz2); result.elements[1 + 2 * 4] = (qyqz2 - qxqw2);
			result.elements[2 + 0 * 4] = (qxqz2 - qyqw2);		   result.elements[2 +  1* 4]= (qyqz2 + qxqw2);         result.elements[2 + 2 * 4] = ((1.0f - qxqx2) - qyqy2);
			return result;
			//return mat4();
		}*/

		mat4 mat4::Scale(const vec3& scale)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scale.x; 
			result.elements[1 + 1 * 4] = scale.y; 
			result.elements[2 + 2 * 4] = scale.z; 
			return result; 
		}
		mat4 mat4::Scale(float x, float y, float z)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = x;
			result.elements[1 + 1 * 4] = y;
			result.elements[2 + 2 * 4] = z;
			return result;
		}
		mat4 mat4::aIMatrix4x4ToMat4(aiMatrix4x4 matrix)
		{
			mat4 result(1.0f); 
		
			//mat4 result(1.0);
			//result.elements[0 + 4 * 0] = matrix.a1;	result.elements[0 + 4 * 1] = matrix.a2;	result.elements[0 + 4 * 2] =matrix.a3;	result.elements[0 + 4 * 3] = matrix.a4;
			//result.elements[1 + 4 * 0] = matrix.b1;	result.elements[1 + 4 * 1] = matrix.b2;	result.elements[1 + 4 * 2] =matrix.b3;		result.elements[1 + 4 * 3] =matrix.b4;
			//result.elements[2 + 4 * 0] = matrix.c1;	result.elements[2 + 4 * 1] = matrix.c2;	result.elements[2 + 4 * 2] =matrix.c3;		result.elements[2 + 4 * 3] =matrix.c4;
			//result.elements[3 + 4 * 0] = matrix.d1; result.elements[3 + 4 * 1] = matrix.d2; result.elements[3 + 4 * 2] =matrix.d3;	result.elements[3 + 4 * 3] = matrix.d4;
			
			result.elements[0 + 4 * 0] = matrix.a1;	result.elements[0 + 4 * 1] = matrix.b1;	result.elements[0 + 4 * 2] = matrix.c1;	result.elements[0 + 4 * 3] = matrix.d1;
			result.elements[1 + 4 * 0] = matrix.a2;	result.elements[1 + 4 * 1] = matrix.b2;	result.elements[1 + 4 * 2] = matrix.c2;		result.elements[1 + 4 * 3] = matrix.d2;
			result.elements[2 + 4 * 0] = matrix.a3;	result.elements[2 + 4 * 1] = matrix.b3;	result.elements[2 + 4 * 2] = matrix.c3;		result.elements[2 + 4 * 3] = matrix.d3;
			result.elements[3 + 4 * 0] = matrix.a4; result.elements[3 + 4 * 1] = matrix.b4; result.elements[3 + 4 * 2] = matrix.c4;	result.elements[3 + 4 * 3] = matrix.d4;
			return result; 
		}
	}
}