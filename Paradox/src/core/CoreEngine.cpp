#include"CoreEngine.h"
#include"Time.h"
#include"Scene.h"
#include"../core/RenderingEngine.h"
#include"PhysicsEngine.h"
using namespace Paradox::component; 
namespace Paradox {
	namespace core {

	CoreEngine::CoreEngine(Scene& game, const char* TITLE, int height, int width,const int frameRate):
		m_Game(game),
		m_FrameRate(frameRate),
		m_PhysicsEngine(PhysicsEngine::Instance())
	{
		m_Window = new Window(TITLE, height, width),
		m_Window->Init(); 
		isRunning = false; 
		m_FrameTime = 1.0f / (m_FrameRate);
		m_RenderingEngine = new RenderingEngine(height, width);
		
		m_Game.setEngine(*this);
	}
	void CoreEngine::start() {
		
		if (isRunning) {
			return; 
		}
		
		run(); 
	}

	RenderingEngine& CoreEngine::getRenderingEngine() 
	{
		// TODO: insert return statement here
		return *m_RenderingEngine;
	}

	Paradox::core::PhysicsEngine& CoreEngine::getPhysicsEngine()
	{
		// TODO: insert return statement here
		return PhysicsEngine::Instance(); 
	}



	
	
	CoreEngine::~CoreEngine()
	{
		
	}

	
	void CoreEngine::run() {
		
		isRunning = true; 
		long frameCounter = 0; 
		int frames = 0; 
		m_Game.init(); 
		long lastTime = Time::getTime();
		double unprocessedTime = 0; 
		
		while (isRunning)
		{
				bool render =false; 
				long startTime = Time::getTime();
				long passedTime = startTime - lastTime; 
				lastTime = startTime; 
				unprocessedTime += passedTime / (double)Time::SECONDS;
				frameCounter += passedTime;
				m_Game.processEvents(); 
				while (unprocessedTime > m_FrameTime)
				{
					render = true; 
					unprocessedTime -= m_FrameTime; 
					m_Game.update( m_FrameTime);
					PhysicsEngine::Instance().update(m_FrameTime); 
					if (frameCounter >= Time::SECONDS)
					{
						std::cout << frames << std::endl; 
						frames = 0; 
						frameCounter = 0; 
					}

				}
			if (render) {
				this->render(); 
				frames++; 
			}
			else {
				
			}
					if (m_Window->getWindowShouldClose())
					{
						stop(); 
					}
		}
		cleanUp();
	}
	void CoreEngine::render()
	{
	//glClearColor(1, 0, 0, 0);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_Game.render(*m_RenderingEngine); 
		m_Window->update(); 
	}
	void CoreEngine::stop() {
		if (!isRunning)
		{
			return; 
		}
		m_Window->CloseWindow(); 
		abort(); 
		isRunning = false; 
	}

	void CoreEngine::cleanUp() {

	}
}
	}