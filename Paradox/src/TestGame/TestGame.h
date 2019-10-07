#pragma once
#include"../core/Scene.h"
#include"../core/Input.h"
#include"../Lights/DirectionalLight.h"
#include"../Lights/PointLight.h"
#include"../Lights/SpotLight.h"
#include"../Components/MeshRenderer.h"
#include"../Components/AnimatedComponent.h"
#include"Behaviors/PlayerBehavior.h"
#include"Behaviors/BallBehavior.h"
#include"Behaviors/SteeringBehavior.h"
#include"../Components/PhysicsObject.h"

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


