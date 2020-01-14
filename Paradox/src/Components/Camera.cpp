#include "Camera.h"
#include"../core/RenderingEngine.h"
#include"../core/GameObject.h"

namespace Paradox {
	namespace component {
		Camera::Camera()
		{
			
		}



		Camera::~Camera()
		{

		}

		Camera::Camera(maths::vec3 startposition, maths::vec3 startUp, GLfloat startpitch, GLfloat startyaw, GLfloat startturnSpeed, GLfloat startmoveSpeed, GLfloat fov, GLfloat aspectRatio, GLfloat near, GLfloat far)
		{	
			WorldUp = startUp;
			front = maths::vec3(0.0f, 0.0f, -1.0f);
			this->position = maths::vec3(0.0f, 0.0f, 0.0f);
			
			pitch = startpitch;
			yaw = startyaw;

			moveSpeed = startmoveSpeed;
			turnSpeed = startturnSpeed;

			distanceFromModel = maths::vec3(4.0f, 4.0f, 4.0f);
			m_Projection = maths::mat4::Perpective(fov, aspectRatio, near, far); 
			updateView();
		}

		maths::mat4 Camera::calculateViewMatrix() const
		{

			glm::mat4 glmResult = glm::lookAt(glm::vec3(position.x, position.y, position.z),
				glm::vec3(position.x + front.x, position.y + front.y, position.z + front.z),
				glm::vec3(Up.x, Up.y, Up.z));
			maths::mat4 Result(1.0);
				
			for (int i = 0; i < 4; i++)
			{

				Result.elements[0 + 4 * i] = glmResult[i].x;
				Result.elements[1 + 4 * i] = glmResult[i].y;
				Result.elements[2 + 4 * i] = glmResult[i].z;
				Result.elements[3 + 4 * i ] = glmResult[i].w;

			}

			return Result;
		}

		auto Camera::calculateViewMatrixGLM() const -> glm::mat4
		{
			glm::mat4 glmResult = glm::lookAt(glm::vec3(position.x, position.y, position.z),
				glm::vec3(position.x + front.x, position.y + front.y, position.z + front.z),
				glm::vec3(Up.x, Up.y, Up.z));
			return glmResult; 
		}

		void Camera::updateView() {
			
			
			front.x = cos(glm::radians(yaw))* cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
			front.normalize();
			right = (front.cross(WorldUp));
			right.normalize();
			Up = right.cross(front);
			Up.normalize();

		}
		void Camera::update(float deltaTime)
		{
			//default controllable 
			this->position = this->m_Parent->getTransform()->getTranslation();
			//std::cout << this->m_Parent->getTransform()->getTranslation().y << std::endl;
		//std::cout << pitch << "  " << yaw<< std::endl;
			this->mouseControl(graphics::Window::getChangeX(), graphics::Window::getChangeY());
			//this->keysControl(graphics::Window::m_Keys);
		}
		void Camera::keysControl(bool * keys)
		{
			
			if (Input::getKey(GLFW_KEY_W) == true)
			{
				std::cout << "w is entered \n";
				position = position - front * moveSpeed;
				//keys[GLFW_KEY_W] = false;
			}
			if (Input::getKey(GLFW_KEY_S) == true)
			{
				std::cout << "s is entered \n";
				position = position + front * moveSpeed;
				//keys[GLFW_KEY_S] = false;
			}
			if (Input::getKey(GLFW_KEY_A) == true)
			{
				std::cout << "a is entered \n";
				position = position - front * moveSpeed;
				//keys[GLFW_KEY_A] = false;
			}
			if (Input::getKey(GLFW_KEY_D) == true)
			{
				std::cout << "s is entered \n";
				position = position + front * moveSpeed;
				//keys[GLFW_KEY_D] = false;
			}
		}

		void Paradox::component::Camera::addToEngine(CoreEngine & coreEngine)
		{
			coreEngine.getRenderingEngine().setMainCamera(this); 
		}

		void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
			xChange *= turnSpeed;
			yChange *= turnSpeed;
			yaw += xChange;
			pitch += yChange;

			if (pitch > 89.0f)
			{
				pitch = 89.0f;
			}
			if (pitch < -89.0f)
			{
				pitch = -89.0f;
			}
			updateView();
		}

		void Camera::MoveCameraForReflection(maths::vec3 ChangePos)
		{
			position = position + ChangePos;
			this->pitch = -pitch;
			updateView();

		}

		const maths::vec3 Camera::getPosition() const
		{
			return position;
		}

		const maths::vec3 Camera::getFront() const
		{
			return front;
		}

		void Camera::setPosition(maths::vec3 pos)
		{
			position = pos + distanceFromModel;
		}

		void Camera::setDirection(maths::vec3 pos)
		{
			front = pos - position;

			front.normalize();

		}

		void Camera::SwitchToFace(int i)
		{
			switch (i)
			{
			case 0: pitch = 0;
				yaw = 90;
				break;

			case 1: pitch = 0;
				yaw = -90;
				break;

			case 2: pitch = -90;
				yaw = 180;
				break;

			case 3: pitch = 90;
				yaw = 180;
				break;

			case 4: pitch = 0;
				yaw = 180;
				break;

			case 5: pitch = 0;
				yaw = 0;
				break;
			}
			updateView();
		}

		maths::mat4 Camera::getProjection() const
		{
			return m_Projection; 
		}

	}
}



