#include "Window.h"

namespace Paradox {
	namespace graphics {
		
		bool Window::m_MouseButtons[MAX_MOUSE_BUTTONS] ;
bool Window::m_Keys[MAX_KEYS];
GLfloat Window::changeX; 
GLfloat Window::changeY;
GLfloat Window::xChangeTemp;
GLfloat Window::yChangeTemp;
		Window::Window(const char* Title,int width, int height)
		{
			m_Width = width;
			m_Height = height;
			m_Title = Title; 
			lastX = 0;
			lastY = 0; 
			changeX = 0; 
			changeY = 0; 
			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false; 
			}
			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}
			mouseMovedFirst = false; 
		}
		
		bool Window::getKeys(int keycode)
		{
			return m_Keys[keycode];
		}
		void Window::Init() 
		{
			if (!glfwInit())
			{
				std::cout << "Failed to Initialize GLFW" << std::endl;
				glfwTerminate(); 

			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL); 
		
			glfwMakeContextCurrent(window);
			
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize glew " << std::endl; 
				
			}
			
			//setting the viewport according to the framebuffer size
			glfwGetFramebufferSize(window, &m_bufferWidth, &m_bufferHeight);
			glViewport(0, 0, m_bufferWidth, m_bufferHeight); 
			glfwSetWindowUserPointer(window, this);
			CreateCallbacks(); 
			ALCdevice* device = alcOpenDevice(NULL);
			ALCcontext* context = alcCreateContext(device, NULL);
			alcMakeContextCurrent(context);
		}

		void Window::update()
		{
			GLenum error = glGetError(); 
			if (error != GL_NO_ERROR)
			{
				std::cout << "Opengl Error : " << error << std::endl;
			}
			glfwPollEvents(); 
			glfwSwapBuffers(window);
		}
		void Window::CreateCallbacks()
		{
			glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
			glfwSetKeyCallback(window, key_callback);
			glfwSetCursorPosCallback(window, mouse_callback);
			glfwSetMouseButtonCallback(window, mouse_button_callback);
		}
		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		bool Paradox::graphics::Window::getWindowShouldClose()
		{
			return glfwWindowShouldClose(window);
		}
		auto Window::CloseWindow() const -> void
		{
			glfwDestroyWindow(window); 
		}
		void Window::framebuffer_size_callback(GLFWwindow * window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
		void Window::key_callback(GLFWwindow * glwindow, int key, int scancode, int action, int mods)
		{
			 
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glwindow));
			if (key >= 0 && key < MAX_KEYS)
			{
				if (action == GLFW_PRESS)
				{
					window->m_Keys[key] = true;
				}
				else if (action == GLFW_RELEASE)
				{
					window->m_Keys[key] = false; 
				}
			}
		}
		void Window::mouse_callback(GLFWwindow * glwindow, double posX, double posY)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glwindow));
			
		
			if (window->mouseMovedFirst == false)
			{
				window->mouseMovedFirst = true; 
				window->lastX = posX;
				window->lastY = posY; 
			}
			//calc change b/w last and current x and y 
			Window::changeX = posX - window->lastX;
			Window::changeY = window->lastY - posY;
			
			//update last x and y 
			window->lastX = posX; 
			window->lastY = posY; 
			
		}
		void Window::mouse_button_callback(GLFWwindow * glwindow, int button, int action, int mods)
		{
			Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glwindow));
			if (button >= 0 && button < MAX_MOUSE_BUTTONS)
			{
				if (action == GLFW_PRESS)
				{
					Window::m_MouseButtons[button] = true;
				
				}
				else if (action == GLFW_RELEASE)
				{
					Window::m_MouseButtons[button] = false;
				}
			}
		}
		bool Window::getMouseKeys(int keycode)
		{
			return  m_MouseButtons[keycode]; 
		}
		GLfloat Window::getChangeX()
		{
			
			Window::xChangeTemp= Window::changeX; 
			Window::changeX = 0.0f;
			return Window::xChangeTemp; 
			
		}
		GLfloat Window::getChangeY()
		{
			Window::xChangeTemp = Window::changeY;
			Window::changeY = 0.0f;
		
			return Window::xChangeTemp;
		}
		Window::~Window()
		{
		}
	}
}