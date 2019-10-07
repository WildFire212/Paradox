#pragma once
#include"GLFW/glfw3.h"
#include"GL/glew.h"
#include<iostream>
#include<alc.h>
#include<al.h>

namespace Paradox {
	namespace graphics
	{
#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 2
		 class Window
	{
	private: 
		int m_Width, m_Height;
		int m_bufferWidth, m_bufferHeight; 
		const char* m_Title; 
		GLFWwindow* window; 
		static bool m_MouseButtons[MAX_MOUSE_BUTTONS];
		GLfloat lastX, lastY; 
		bool mouseMovedFirst; 
		
	public:
		static GLfloat changeX, changeY; 
		static GLfloat xChangeTemp, yChangeTemp; 
		static bool m_Keys[MAX_KEYS];
		void Init()  ; 
		void clear() const; 
		void update();
		bool getWindowShouldClose();
		Window(const char* Title, int width, int height);
		static bool getKeys(int keycode); 
		static bool getMouseKeys(int keycode); 
		static GLfloat getChangeX(); 
		static GLfloat getChangeY();
		~Window();
	private: 
		void CreateCallbacks(); 
		static void  framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void key_callback(GLFWwindow* glwindow, int key, int scancode, int action, int mods);
		static void mouse_callback(GLFWwindow* glwindow, double xPos, double yPos);
		static void mouse_button_callback(GLFWwindow* glwindow, int button, int action, int mods);
		
		//helper function for static array initialization
		bool* getArray(int size); 
		};
}}
