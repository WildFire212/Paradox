#pragma once
#include"../maths/maths.h"
using namespace Paradox;
namespace Paradox {

	class Transform {
	private: 
		maths::vec3 translation; 
		maths::quaternion rotation; 
		maths::vec3 scale; 
	private: 
		maths::vec3 m_oldScale; 
		maths::quaternion m_oldRot; 
		maths::vec3 m_oldTranslation; 

		Transform* m_Parent; 
		maths::mat4  m_ParentMatrix;

		
	public: 
		Transform(); 

		void update() ;
		auto hasChanged() -> bool;
		
		 auto getTransformation() -> const maths::mat4 ; 
		 auto getParentMatrix() -> const maths::mat4  ; 
		 auto getTranslation() -> const maths::vec3; 
		 auto getScale() -> const maths::vec3;



		 void setTranslation(maths::vec3 translation); 
		void setRotation(maths::quaternion rotation);
		void setScale(maths::vec3 scale); 
		
		void setTranslation(float x, float y , float z ); 
		void setRotation(float x, float y , float z,float w ); 
		void setScale(float x, float y , float z ); 
		void setParent(Transform* parent); 

		void rotate(maths::vec3 axis, float angle); 
		void move(maths::vec3 move); 

	private: 
		auto initTranslationMatrix() const -> const maths::mat4; 
		auto initScaleMatrix() const -> const maths::mat4; 
		auto initRotationMatrix() const -> const maths::mat4; 
	};
}
