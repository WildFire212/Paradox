#include "TestGame.h"
#include"Lights/DirectionalLight.h"
#include"Lights/SpotLight.h"
#include"Lights/PointLight.h"
#include"Components/MeshRenderer.h"
#include"Components/PhysicsObject.h"
#include"Physics/AABBCollider.h"
#include"Physics/SphereCollider.h"
#include"Physics/PlaneCollider.h"
#include"Components/AnimatedComponent.h"
#include"Behaviors/PlayerBehavior.h"
#include"Behaviors/BallBehavior.h"
#include"Behaviors/SteeringBehavior.h"
#include"graphics/Window.h"
#include"PostEffects/Skybox.h"
TestGame::TestGame()
= default;

void TestGame::init()
{


	//lights
	auto* Lights = new GameObject(); 

	auto* pointLightObject = new GameObject();
	auto* directLightObject= new GameObject();
	auto* spotLightObject = new GameObject();


	auto* ptLight = new PointLight(0.0F, 0.0, 1.0F, 0.2F, 1.0F,maths::vec3(0, -0.9F, 0.0F),0.7F, 0.6F, 1.0F);
	auto* dlight = new DirectionalLight(1.0F, 1.0f, 1.0F, 0.8F,0.8F, maths::vec3(0.0F, -1.0F, -1.0F));
	auto* spotLight = new SpotLight(1.0F, 0.0F, 0.0F, 0.0F, 1.0F, maths::vec3(0.0F, 0.8F, 0.0F), vec3(0.0F, -1.0F, 0.0F), 1.0F, 0.0F, 0.0F, 20.0F);

	pointLightObject->addComponent(ptLight);
	directLightObject->addComponent(dlight);
	spotLightObject->addComponent(spotLight);

	//Lights->addChild(pointLightObject);
	Lights->addChild(directLightObject);
	//Lights->addChild(spotLightObject); 
	Lights->setName("Lights"); 
	addObject(Lights); 
	
	//floor

	auto* floorObject = new GameObject("Floor"); 
	
	std::vector<GLfloat> floorVertices = {
		-30.0F, 0.0F, -30.0F,
		30.0F,  0.0F, -30.0F,
		-30.0F, 0.0F, 30.0F,
		30.0F,  0.0F, 30.0F,
	};
	std::vector<GLushort> floorIndices ={
		0, 2, 1,
		1, 2, 3
	};
	std::vector<GLfloat> floorNormals = {
		0.0F,-1.0F, 0.0F,
		0.0F,-1.0F, 0.0F,
		0.0F,-1.0F, 0.0F,
		0.0F,-1.0F, 0.0F
	};
	std::vector<GLfloat> FloortexCoords = {
			0.0F, 0.0F,
			10.0F, 0.0F,
			0.0F, 10.0F,
			10.0F, 10.0F
	};

	Texture texture("Textures/DirtyBrick_S.jpg");
	Texture normalTexture("Textures/DirtyBrick_N.jpg");
	auto* material = new Material(texture, 0.1F, 0.1F, normalTexture);

	//mesh Renderer
	Mesh* floorMesh = new Mesh(floorVertices, floorIndices, 12, 6, FloortexCoords, material, floorNormals, false);
	auto* floorMeshRenderer = new MeshRenderer(floorMesh,false);
	PhysicsObject* planePhysicsObj = new PhysicsObject(new PlaneCollider(vec3(0.0f, 1.0f, 0.0f),0.0f), 3.0f, 0.0f, false);
	////add component 
	floorObject->addComponent(planePhysicsObj);
	floorObject->addComponent(floorMeshRenderer); 
	floorObject->setName("Floor");
	addObject(floorObject); 
	

		
	//world 
	GameObject* worldObject= new GameObject("World"); 
	//fence1
	GameObject* fenceObject = new GameObject("Fence");
	Mesh* fenceMesh = new Mesh("Models/wooden_fence.fbx");
	PhysicsObject* fencePhysicsObject = new PhysicsObject(new AABBCollider(fenceMesh->getColliderData().m_MinExtents, fenceMesh->getColliderData().m_MaxExtents), 50.0f, 0.0f, false);
	fenceObject->getTransform()->setTranslation(vec3(0.19991f,0.9517f,28.8f));
	fenceObject->getTransform()->setScale(vec3(0.5f, 1.6f,0.5f));
	fenceObject->getTransform()->setRotation(quaternion(0.f, 0.f, 0.7071068f, 0.7071068f));
	BallBehavior* b = new BallBehavior();
	fenceObject->addComponent(b);

	//fenceObject->addComponent(fencePhysicsObject);
	fenceObject->addComponent(new MeshRenderer(fenceMesh, true));
	worldObject->addChild(fenceObject);
	
	//fence2
	GameObject* fenceObject2 = new GameObject("Fence2");
	fenceObject2->getTransform()->setTranslation(vec3(0.19991f,0.9517f,-28.8f));
	fenceObject2->getTransform()->setScale(vec3(0.5f, 1.6f,0.5f));
	fenceObject2->getTransform()->setRotation(quaternion(0.f, 0.f, 0.7071068f, 0.7071068f));
	
	//fenceObject->addComponent(fencePhysicsObject);
	fenceObject2->addComponent(new MeshRenderer(fenceMesh, true));
	worldObject->addChild(fenceObject2);
	
	
	//castle
	auto* zombieMesh = new Mesh("Models/8Ball.fbx");
	GameObject* castleObject = new GameObject("House");
	
	Mesh* house = new Mesh("Models/medieval house.obj");
	PhysicsObject* housePhysicsObject = new PhysicsObject(new AABBCollider(house->getColliderData().m_MinExtents, house->getColliderData().m_MaxExtents) , 100.0f, 0.0f,true);
	
	castleObject->getTransform()->setTranslation(vec3(5.00002,0.2258307f ,- 6.8f));
	castleObject->addComponent(new MeshRenderer(house,true));
	castleObject->addComponent(housePhysicsObject); 
	worldObject->addChild(castleObject);
	

	//tractor 
	GameObject* tractorObject= new GameObject("Tractor");
	Mesh* tractorMesh = new Mesh("Models/Car_Tractor_01.obj");
	//PhysicsObject* tractorPhysicsObject = new PhysicsObject(new AABBCollider(tractorMesh->getColliderData().m_MinExtents, tractorMesh->getColliderData().m_MaxExtents), 50.0f, 0.0f, true);
	PhysicsObject* tractorPhysicsObject = new PhysicsObject(new SphereCollider(zombieMesh->getColliderData().m_Center, zombieMesh->getColliderData().m_Radius), 10.0F, 0.0F, true);
	
	//tractorObject->getTransform()->setScale(vec3(0.02f, 0.02f, 0.02f));
	tractorObject->getTransform()->setTranslation(vec3(-15.5f,0.0517222f,13.8f));
	tractorObject->addComponent(tractorPhysicsObject); 
	tractorObject->addComponent(new MeshRenderer(zombieMesh, true));
	worldObject->addChild(tractorObject);

	//animated model 
	auto* animatedManObject = new GameObject();
	auto* animatedShader = new Shader("src/Shaders/GLSLShaders/GBufferAnimationShader.vert", "src/Shaders/GLSLShaders/GBufferShader.frag");
	animatedManObject->addComponent(new AnimatedComponent(new AnimatedModel("Models/model.dae"), animatedShader));

	//worldObject->addChild(animatedManObject); 
	




	//characters

	//zombie 1
	auto* zombieObject1 = new GameObject();
	//auto* zombieMesh = new Mesh("Models/8Ball.fbx"); 
	auto* zombieMeshRenderer = new MeshRenderer(zombieMesh,true);
	auto* zombiePhysicsObject = new PhysicsObject(new SphereCollider(zombieMesh->getColliderData().m_Center, zombieMesh->getColliderData().m_Radius), 10.0F, 0.0F, true);
	zombieObject1->getTransform()->setTranslation(vec3(25.f, 3.f, 25.0f));
	
	SteeringBehavior* zombieBehavior1 = new SteeringBehavior(*this);
	zombieBehavior1->m_MaxSpeed = 5.0f; 
	zombieBehavior1->addToList(vec3(25, 0, -25));
	zombieBehavior1->addToList(vec3(-10, 0, -25));
	zombieBehavior1->addToList(vec3(25, 0, -25));
	zombieBehavior1->addToList(vec3(25, 0, 25)); 
	zombieObject1->addComponent(zombieBehavior1);
	zombieObject1->addComponent(zombiePhysicsObject);
	zombieObject1->addComponent(zombieMeshRenderer);
	zombieObject1->setName("Zombie1");
	addObject(zombieObject1);

	//zombie 2
	auto* zombieObject2 = new GameObject();
	//auto* zombieMesh = new Mesh("Models/8Ball.fbx"); 
	auto* zombieMeshRenderer2 = new MeshRenderer(zombieMesh,true);
	auto* zombiePhysicsObject2 = new PhysicsObject(new SphereCollider(zombieMesh->getColliderData().m_Center, zombieMesh->getColliderData().m_Radius), 10.0F, 0.0F, true);
	zombieObject2->getTransform()->setTranslation(vec3(-20.f, 3.f, -20.0f));

	SteeringBehavior* zombieBehavior2 = new SteeringBehavior(*this);
	zombieBehavior2->m_MaxSpeed = 5.0f;
	zombieBehavior2->addToList(vec3(-5, 0, -20));
	zombieBehavior2->addToList(vec3(-5, 0, 0));
	zombieBehavior2->addToList(vec3(-20, 0, 0));
	zombieBehavior2->addToList(vec3(-20, 0, -20));
	zombieObject2->addComponent(zombieBehavior2);
	zombieObject2->addComponent(zombiePhysicsObject2);
	zombieObject2->addComponent(zombieMeshRenderer2);
	zombieObject2->setName("Zombie2");
	addObject(zombieObject2);

	
	//zombie 3
	auto* zombieObject3 = new GameObject();
	//auto* zombieMesh = new Mesh("Models/8Ball.fbx"); 
	auto* zombieMeshRenderer3 = new MeshRenderer(zombieMesh,true);
	auto* zombiePhysicsObject3 = new PhysicsObject(new SphereCollider(zombieMesh->getColliderData().m_Center, zombieMesh->getColliderData().m_Radius), 10.0F, 0.0F, true);
	zombieObject3->getTransform()->setTranslation(vec3(20.f, 3.f, -20.0f));

	SteeringBehavior* zombieBehavior3 = new SteeringBehavior(*this);
	zombieBehavior3->m_MaxSpeed = 5.0f;
	zombieBehavior3->addToList(vec3(20, 0, 15));
	zombieBehavior3->addToList(vec3(5, 0, 15));
	zombieBehavior3->addToList(vec3(5, 0, 0));
	zombieBehavior3->addToList(vec3(15, 0,0));
	zombieBehavior3->addToList(vec3(15, 0,-20));
	zombieBehavior3->addToList(vec3(20, 0,-20));
	zombieObject3->addComponent(zombieBehavior3);
	zombieObject3->addComponent(zombiePhysicsObject3);
	zombieObject3->addComponent(zombieMeshRenderer3);
	zombieObject3->setName("Zombie3");
	addObject(zombieObject3);

	
	//zombie 4
	auto* zombieObject4 = new GameObject();
	//auto* zombieMesh = new Mesh("Models/8Ball.fbx"); 
	auto* zombieMeshRenderer4 = new MeshRenderer(zombieMesh,true);
	auto* zombiePhysicsObject4 = new PhysicsObject(new SphereCollider(zombieMesh->getColliderData().m_Center, zombieMesh->getColliderData().m_Radius), 10.0F, 0.0F, true);
	zombieObject4->getTransform()->setTranslation(vec3(-20.f, 3.f, 20.0f));

	SteeringBehavior* zombieBehavior4 = new SteeringBehavior(*this);
	zombieBehavior4->m_MaxSpeed = 5.0f;
	zombieBehavior4->addToList(vec3(-25, 0, 20));
	zombieBehavior4->addToList(vec3(-25, 0, 5));
	zombieBehavior4->addToList(vec3(-10, 0, 5));
	zombieBehavior4->addToList(vec3(-10, 0, 20));
	zombieBehavior4->addToList(vec3(-20, 0, 20));
	zombieObject4->addComponent(zombieBehavior4);
	zombieObject4->addComponent(zombiePhysicsObject4);
	zombieObject4->addComponent(zombieMeshRenderer4);
	zombieObject4->setName("Zombie4");
	addObject(zombieObject4);

	



	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");
	//player
	auto* playerObject = new GameObject("Player");
	//playerObject->getTransform()->setTranslation(vec3(0.F, 15.F, 0.0F));
	auto* playerBehavior = new PlayerBehavior();

	auto* camera = new Camera(maths::vec3(0, 0.0F, 0.0F), maths::vec3(0.0F, 1.0F, 0.0F), -89.0F, 0.0F,0.8F, 0.5F, 45.0F, 1.0F, 0.1F, 1000.0F);
	playerObject->addComponent(camera);
	playerObject->getTransform()->setTranslation(vec3(10.0f,3.0f, 0.0f)); 
	PhysicsObject* playerPhysicsObject = new PhysicsObject(new SphereCollider(vec3(10.0f, 0.0f, 0.0f),2.0f),10.0f, vec3(0,0,0),true); 
//	playerObject->addComponent(playerPhysicsObject); 
	playerObject->addComponent(playerBehavior);
	playerObject->setName("Player");
	worldObject->addChild(playerObject);
	
	addObject(worldObject); 
	 
	addToForwardRendererList(Skybox::getInstance(skyboxFaces)); 

	}
	
	
	

void TestGame::processEvents()
{
	Scene::processEvents(); 
	
}


void TestGame::update(float deltaTime)
{

	Scene::update(deltaTime); 
	//std::cout << findObject("Camera")->getTransform()->translation.x << std::endl;
	
}

void TestGame::render( RenderingEngine & renderingEngine) 
{
	Scene::render(renderingEngine); 
}




TestGame::~TestGame()= default;
