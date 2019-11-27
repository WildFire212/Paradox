#include "TestGame.h"
#include"../Physics/SphereCollider.h"
#include"../Physics/PlaneCollider.h"
#include"../Physics/TerrainCollider.h"
#include"../Physics/AABBCollider.h"
#include"../Components/Terrain.h"
TestGame::TestGame()
= default;

void TestGame::init()
{


	//lights
	auto* Lights = new GameObject(); 

	auto* pointLightObject = new GameObject();
	auto* directLightObject= new GameObject();
	auto* spotLightObject = new GameObject();


	auto* ptLight = new PointLight(0.0F, 0.0, 1.0F, 0.2F, 1.0F,glm::vec3(0, -0.9F, 0.0F),0.7F, 0.6F, 1.0F);
	auto* dlight = new DirectionalLight(1.0F, 1.0f, 1.0F, 0.8F,0.8F, glm::vec3(0.0F, -1.0F, -1.0F));
	auto* spotLight = new SpotLight(1.0F, 0.0F, 0.0F, 0.0F, 1.0F, glm::vec3(0.0F, 0.8F, 0.0F), glm::vec3(0.0F, -1.0F, 0.0F), 1.0F, 0.0F, 0.0F, 20.0F);

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

	Texture texture("Textures/grass.jpg");	
	auto* material = new Material(texture, 0.1F, 0.1F, texture);

	//mesh Renderer
	Mesh* floorMesh = new Mesh(floorVertices, floorIndices, 12, 6, FloortexCoords, material, floorNormals, false);
	auto* floorMeshRenderer = new MeshRenderer(floorMesh,true);
	PhysicsObject* planePhysicsObj = new PhysicsObject(new PlaneCollider(vec3(0.0f, 1.0f, 0.0f),0.0f), 3.0f, 0.0f, false);
	////add component 
	floorObject->addComponent(planePhysicsObj);
	floorObject->addComponent(floorMeshRenderer); 
	floorObject->setName("Floor");
	addObject(floorObject); 
	

	//terrain 
	/*auto* terrainObject = new GameObject("Terrain");
	auto* terrain = new Terrain(0, 0, new Texture("Textures/Grass.jpg"), "Textures/Heightmap.png"); 
	auto* terrainCollider = new TerrainCollider(*terrain); 
	auto* terrainPhysicsObject = new PhysicsObject(terrainCollider, 1.0F, 0.0F, false);
	terrainObject->addComponent(terrainPhysicsObject); 
	terrainObject->addComponent(terrain);
	
	addObject(terrainObject);*/
		
	//world 
	GameObject* worldObject= new GameObject("World"); 
	
	//castle
	GameObject* castleObject = new GameObject();
	Mesh* house = new Mesh("Models/medieval house.obj");
	PhysicsObject* housePhysicsObject = new PhysicsObject(new AABBCollider(house->getColliderData().m_MinExtents, house->getColliderData().m_MaxExtents) , 100.0f, 0.0f,true);
	castleObject->addComponent(new MeshRenderer(house,true));
	//castleObject->getTransform()->setScale(vec3(0.2f, 0.2f, 0.2f));
	//castleObject->getTransform()->setRotation(quaternion(0.7f, 0.7f, 0.7f, 0.7f));
	//castleObject->getTransform()->setTranslation(vec3(0, 0.5F, 0.0F)); 
	BallBehavior* houseBehaviour = new BallBehavior(); 
	castleObject->addComponent(houseBehaviour); 
	castleObject->addComponent(housePhysicsObject); 
	//street1->getTransform()->setScale(0.02f, 0.02f, 0.02f);
	//street1->getTransform()->setScale(5.0f, 0.0f, 5.0f);
	worldObject->addChild(castleObject);
	
	//GameObject* street2 = new GameObject();
	//street2->addComponent(new MeshRenderer(street));
	//street2->getTransform()->setScale(5.0f, 0.0f, 5.0f);
	//street2->getTransform()->setTranslation(0.0f, 10.0f, 0.0f);
	//worldObject->addChild(street2);

	//animated model 
	auto* animatedManObject = new GameObject(); 
	auto * animatedShader = new Shader("src/Shaders/GLSLShaders/GBufferAnimationShader.vert", "src/Shaders/GLSLShaders/GBufferShader.frag");
	animatedManObject->addComponent(new AnimatedComponent(new AnimatedModel("Models/model.dae"),animatedShader));
	
	//worldObject->addChild(animatedManObject); 


//characterrs
	//ball 1
		auto* ballObject = new GameObject("Ball"); 
	auto* ballMeshRenderer = new MeshRenderer(new Mesh("Models/Car_Tractor_01.obj"),true); 
	auto* ballPhysicsObject = new PhysicsObject(new SphereCollider(vec3(-500.0F, 11.0F, 5.F), 1.0F), 10.0F, 0.0F,true);
	ballObject->getTransform()->setScale( vec3(0.02f, 0.02f, 0.02f)); 
	ballObject->getTransform()->setRotation(quaternion(0, 0, 0.7071068, 0.7071068));
	ballObject->getTransform()->setTranslation( vec3(5.0F, 2.F, 5.0F)); 
	
	//ballObject->getTransform()->setTranslation( vec3(5.0F, 11.F, 5.0F)); 
	//ballPhysicsObject->addForce(vec3(-1.0f, -9.8f, 0.0f)); 
	//SteeringBehavior* steeringBehavior = new SteeringBehavior(*this);
	ballPhysicsObject->m_UseGravity = true; 
	//steeringBehavior->addToList(vec3(0, 5, 0));
	//steeringBehavior->addToList(vec3(5, 0, 0));
	//steeringBehavior->addToList(vec3(0, 0, 5));
	//steeringBehavior->addToList(vec3(5, 0, 5));
	//auto* ballBehavior = new BallBehavior(); 

	//ballObject->addComponent(ballBehavior); 
	ballObject->addComponent(ballPhysicsObject); 
	//ballObject->addComponent(steeringBehavior); 
	ballObject->addComponent(ballMeshRenderer); 
	ballObject->setName("Ball");
	addObject(ballObject); 
	

	//ball 2 
	GameObject* ballObject2 = new GameObject(); 
	MeshRenderer* ballMeshRenderer2= new MeshRenderer(new Mesh("Models/8Ball.fbx"),true); 
	PhysicsObject* ballPhysicsObject2 = new PhysicsObject(new SphereCollider(vec3(5.0F, 4.0F, 5.F), 1.0f), 100.0f,0.0f,true);
	ballObject2->getTransform()->setTranslation(vec3(5.0F, 3.0f, 0.0F));
	//ballObject2->getTransform()->setScale(vec3(0.02f, 0.02f, 0.02f));
	//ballObject2->getTransform()->setTranslation(vec3(5.0F, 11.F, 5.0F));
	SteeringBehavior* steering = new SteeringBehavior(*this); 
	steering->m_MaxSpeed = 5.0f; 
	steering->addToList(vec3(20, 0, -20.0f));
	steering->addToList(vec3(-20, 0, 20.0f));
	steering->addToList(vec3(-20.0f, 0, -20.0f));
	steering->addToList(vec3(20.0f, 0, 20.0f));

	ballObject2->addComponent(ballPhysicsObject2); 
	ballObject2->addComponent(steering); 
	ballObject2->addComponent(ballMeshRenderer2); 
	worldObject->addChild(ballObject2); 

	
	//player
	auto* playerObject = new GameObject("Player");
	//playerObject->getTransform()->setTranslation(vec3(0.F, 15.F, 0.0F));
	auto* playerBehavior = new PlayerBehavior();

	auto* camera = new Camera(maths::vec3(0, 0.0F, 0.0F), maths::vec3(0.0F, 1.0F, 0.0F), -89.0F, 0.0F,0.8F, 0.5F, 45.0F, 1.0F, 0.1F, 1000.0F);
	playerObject->addComponent(camera);
	playerObject->getTransform()->setTranslation(vec3(10.0f,2.0f, 0.0f)); 
	PhysicsObject* playerPhysicsObject = new PhysicsObject(new SphereCollider(vec3(10.0f, 0.0f, 0.0f),0.2f),100.0f, vec3(0,0,0),true); 
	//playerObject->addComponent(playerPhysicsObject); 
	playerObject->addComponent(playerBehavior);
	playerObject->setName("Player");
	worldObject->addChild(playerObject);

	 


	addObject(worldObject); 
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
