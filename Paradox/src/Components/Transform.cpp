#include "Transform.h"
#include"../../src/core/GameObject.h"
using namespace Paradox::maths; 
namespace Paradox {
	Transform::Transform() :
		translation(0.0f, 0.0f, 0.0f),
		rotation(0,0,0,1.0f),
		scale(1,1,1),
		m_ParentMatrix(mat4::Identity())	
	{
		
	}
	void Transform::update()
	{
		if (m_oldTranslation != vec3(0, 0, 0)) {
			m_oldTranslation = translation; 
			m_oldScale = scale;
			m_oldRot = rotation; 
			


		}
		else {
			m_oldTranslation = translation + 0.1f; //vec3(0, 0, 0)+ (1.0f); 
				m_oldRot = rotation.Multiply(0.5f);//quaternion(0,0,0,0).Multiply(0.5f);
				m_oldScale = scale + 1.0f;//vec3(0, 0, 0) + 1.0f;
		
		}

		//if (/*m_ParentMatrix != nullptr &&*/ m_Parent->hasChanged())
		//{
		//	m_ParentMatrix =  m_Parent->getTransformation();
		//}
	}
	bool Transform::hasChanged()
	{

		if (this->m_Parent != nullptr)
		{
			if (m_Parent->hasChanged())
				return true;
		}
		if (scale != m_oldScale)
		{
			return true;
		}
		if (rotation != m_oldRot)
		{
			return true; 
		}
		if (translation != m_oldTranslation) {
			return true; 
		}
		return false;	
	}
	const maths::mat4 Transform::getTransformation()  
{
	maths::mat4 translationMatrix = maths::mat4::Translate(this->translation);
	maths::mat4 rotationMatrix = maths::mat4::Rotate(this->rotation); 
		maths::mat4 scaleMatrix= maths::mat4::Scale(this->scale);
	return getParentMatrix()* translationMatrix* rotationMatrix * scaleMatrix;
	//return translationMatrix * scaleMatrix;
}

	const maths::mat4 Transform::getParentMatrix() 
	 {
		if (m_Parent!=nullptr && m_Parent->hasChanged())
		{
		 m_ParentMatrix = m_Parent->getTransformation(); 
		}
		 return m_ParentMatrix; 
	 }

	auto Transform::getTranslation() -> const maths::vec3
	{
		return translation; 
	}

	 auto Transform::getScale()  -> const maths::vec3
	{
		return scale;

	}

 void Transform::setTranslation(maths::vec3 translation)
{
	 this->translation = translation; 
}

 void Transform::setRotation(maths::quaternion rotation)
{
	 this->rotation = rotation; 

}

 void Transform::setScale(maths::vec3 scale)
{
	 this->scale = scale;
}


 void Transform::setTranslation(float x, float y, float z)
{
	 this->translation.x = x; 
	 this->translation.y = y; 
	 this->translation.z = z; 
}

 void Transform::setRotation(float x, float y, float z,float w)
{
	 this->rotation.x = x;
	 this->rotation.y = y;
	 this->rotation.z = z;
	 this->rotation.w = w; 
}

 void Transform::setScale(float x, float y, float z)
{
	 this->scale.x = x;
	 this->scale.y = y;
	 this->scale.z = z;
}

 void Transform::setParent(Transform * parent)
 {
	 m_Parent = parent;
 }

 void Transform::rotate(vec3 axis, float angle)
 {
	 rotation = (quaternion(axis, angle).Multiply(rotation));
	 rotation.normalize(); 
 }

 void Transform::move(maths::vec3 move)
 {
	 translation += move; 
 }



 const maths::mat4 Transform::initTranslationMatrix() const
 {
	 return maths::mat4::Translate(this->translation);
 }

 const maths::mat4 Transform::initScaleMatrix() const
 {
	 return maths::mat4();
 }

 const maths::mat4 Transform::initRotationMatrix() const
 {
	 return maths::mat4();
 }


}

