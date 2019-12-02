#pragma once
#include"core/Scene.h"

using namespace Paradox::core;
class TestGame :
	public Scene
{
private: 

	

public:
	TestGame();
	void init() override; 
	void processEvents() override; 
	void update(float deltaTime) override;
	void render( RenderingEngine& renderingEngine) override; 
	~TestGame();
};


