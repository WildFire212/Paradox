#pragma once
#include"../graphics/Window.h"

using namespace Paradox::graphics; 

namespace Paradox {
	namespace graphics { class RenderingEngine;  }
	namespace core { class PhysicsEngine;  }
	namespace core {
	class Scene; 
	
	class CoreEngine {
	private:
		
		Scene& m_Game;
		Window* m_Window;
		const int m_FrameRate; 
		double m_FrameTime; 
		bool isRunning; 
		RenderingEngine* m_RenderingEngine; 
		Paradox::core::PhysicsEngine& m_PhysicsEngine; 
	public:
		CoreEngine(Scene& game, const char* TITLE, int height, int width, const int frameTime);
		void start();
		~CoreEngine(); 

		RenderingEngine& getRenderingEngine(); 
		Paradox::core::PhysicsEngine& getPhysicsEngine();
	private:
		void run();
		void render(); 
		void stop();
		void cleanUp();




		

	};


	}
}