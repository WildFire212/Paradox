#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"../maths/maths.h"
#include"../Components/Component.h"
#include"../core/Input.h"

using namespace Paradox::core; 
namespace Paradox {
	namespace component {
		class Camera : public Component {
		public:
			Camera();
			Camera(maths::vec3 startposition, maths::vec3 startUp, GLfloat startpitch, GLfloat startyaw, GLfloat startturnSpeed, GLfloat  startmoveSpeed,GLfloat fov, GLfloat aspectRatio, GLfloat near, GLfloat far);
			~Camera();
			auto calculateViewMatrix() const -> maths::mat4;
			auto calculateViewMatrixGLM() const -> glm::mat4;
			void updateView() ;
			void update(float deltaTime) override;

			void addToEngine(CoreEngine& coreEngine) override;
			void mouseControl(GLfloat xChange, GLfloat yChange);
			void keysControl(bool* keys);

			void MoveCameraForReflection(maths::vec3 ChangePos);

			auto getPosition() const -> const maths::vec3;
			void setPosition(maths::vec3 pos);
			void setDirection(maths::vec3 pos);
			void SwitchToFace(int size);
			maths::vec3 position;

			auto getProjection() const -> maths::mat4; 

			//getters 
			
			auto getFront() const -> const maths::vec3;
			
		private:

			maths::vec3 front;
			maths::vec3  Up;

			GLfloat yaw;
			GLfloat pitch;

			GLfloat moveSpeed;
			GLfloat turnSpeed;

			maths::vec3 right;
			maths::vec3 WorldUp;

			maths::vec3 distanceFromModel;

			maths::mat4 m_Projection; 
		};

	}
}