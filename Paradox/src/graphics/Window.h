#pragma once
#define WINDOW_H
#include<GL/glew.h>
#include"GLFW/glfw3.h"
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
		auto getWindowShouldClose() -> bool;
		auto CloseWindow()const -> void ;
		
		Window(const char* Title, int width, int height);
		static auto getKeys(int keycode) -> bool; 
		static auto getMouseKeys(int keycode) -> bool; 
		static auto getChangeX() -> GLfloat; 
		static auto getChangeY() -> GLfloat;
		~Window();
	private: 
		void CreateCallbacks(); 
		static void  framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void key_callback(GLFWwindow* glwindow, int key, int scancode, int action, int mods);
		static void mouse_callback(GLFWwindow* glwindow, double xPos, double yPos);
		static void mouse_button_callback(GLFWwindow* glwindow, int button, int action, int mods);
		
		//helper function for static array initialization
		auto getArray(int size) -> bool*; 
		};
}}
