#include "TestGame.h"
#include"../Physics/SphereCollider.h"
#include"../Physics/PlaneCollider.h"
#include"../Physics/TerrainCollider.h"
#include"../Components/Terrain.h"
TestGame::TestGame()
{
	
}

void TestGame::init()
{

	//player
	GameObject* playerObject = new GameObject("Player");
	playerObject->getTransform()->translation = vec3(0.f, 10.f, 0.0f);
	PlayerBehavior* playerBehavior = new PlayerBehavior();

	Camera* camera = new Camera(maths::vec3(0, 0.2f, 0.3f), maths::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.8f, 0.5f, 45.0f, 1.0f, 0.1f, 1000.0f);
	playerObject->addComponent(playerBehavior);
	playerObject->addComponent(camera);
	playerObject->setName("Player");
	addObject(playerObject);



	//lights
	GameObject* Lights = new GameObject(); 

	GameObject* pointLightObject = new GameObject();
	GameObject* directLightObject= new GameObject();
	GameObject* spotLightObject = new GameObject();


	PointLight* ptLight = new PointLight(0.0f, 0.0, 1.0f, 0.2f, 1.0f,glm::vec3(0, -0.9f, 0.0f),0.7f, 0.6f, 1.0f);
	DirectionalLight* dlight = new DirectionalLight(1.0f, 1.0, 1.0f, 0.8f, 0.9f, glm::vec3(0.0f, -1.0f, -1.0f));
	SpotLight* spotLight = new SpotLight(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, glm::vec3(0.0f, 0.8f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), 1.0f, 0.0f, 0.0f, 20.0f);

	pointLightObject->addComponent(ptLight);
	directLightObject->addComponent(dlight);
	spotLightObject->addComponent(spotLight);

	//Lights->addChild(pointLightObject);
	Lights->addChild(directLightObject);
	//Lights->addChild(spotLightObject); 
	Lights->setName("Lights"); 
	addObject(Lights); 
	
	//floor 
	GameObject* floorObject = new GameObject(); 
	
	std::vector<GLfloat> floorVertices = {
		-3.0f, -1.0f, -3.0f,
		3.0f,  -1.0f, -3.0f,
		-3.0f, -1.0f, 3.0f,
		3.0f,  -1.0f, 3.0f,
	};
	std::vector<GLushort> floorIndices ={
		0, 2, 1,
		1, 2, 3
	};
	std::vector<GLfloat> floorNormals = {
		0.0f,-1.0f, 0.0f,
		0.0f,-1.0f, 0.0f,
		0.0f,-1.0f, 0.0f,
		0.0f,-1.0f, 0.0f
	};
	std::vector<GLfloat> FloortexCoords = {
			0.0f, 0.0f,
			10.0f, 0.0f,
			0.0f, 10.0f,
			10.0f, 10.0f
	};

	Texture texture("Textures/Test.png");
	Material* material = new Material(texture, 0.1f, 0.1f, texture);

	//mesh Renderer
	Mesh* floorMesh = new Mesh(floorVertices, floorIndices, 12, 6, FloortexCoords, material, floorNormals, false);
	MeshRenderer* floorMeshRenderer = new MeshRenderer(floorMesh);
	//add component 
	floorObject->addComponent(floorMeshRenderer); 
	floorObject->setName("Floor");
	addObject(floorObject); 
	

	//terrain 
	GameObject* terrainObject = new GameObject("Terrain");
	Terrain* terrain = new Terrain(0, 0, new Texture("Textures/Grass.jpg"), "Textures/Heightmap.png"); 
	TerrainCollider* terrainCollider = new TerrainCollider(*terrain); 
	PhysicsObject* terrainPhysicsObject = new PhysicsObject(terrainCollider, 1.0f, 0.0f, false);
	terrainObject->addComponent(terrainPhysicsObject); 
	terrainObject->addComponent(terrain);
	
	addObject(terrainObject);
	
	//world 
	GameObject* worldObject= new GameObject(); 
	
	//castle
	GameObject* castleObject = new GameObject();
	castleObject->addComponent(new MeshRenderer(new Mesh("Models/Castle/Castle OBJ.obj")));
	castleObject->getTransform()->translation -= vec3(0, 10.f, 0.0f); 
	//plane 
	//PhysicsObject* planePhysicsObj = new PhysicsObject(new PlaneCollider(vec3(0.0f,1.0f,0.0f) ,0.0f),3.0f,0.0f	,false); 
	//castleObject->addComponent(planePhysicsObj); 
	//castleObject->getTransform()->setScale(0.5f, 0.5f, 0.5f);
	//castleObject->getTransform()->setTranslation(0.0f, 5.f, 0.5f);
	worldObject->addChild(castleObject);

	//animated model 
	GameObject* animatedManObject = new GameObject(); 
	Shader * animatedShader = new Shader("src/Shaders/GLSLShaders/GBufferAnimationShader.vert", "src/Shaders/GLSLShaders/GBufferShader.frag");
	animatedManObject->addComponent(new AnimatedComponent(new AnimatedModel("AnimatedModels/model.dae"),animatedShader));
	//worldObject->addChild(animatedManObject); 

	//ball 1
		GameObject* ballObject = new GameObject(); 
	MeshRenderer* ballMeshRenderer = new MeshRenderer(new Mesh("Models/8Ball.fbx")); 
	PhysicsObject* ballPhysicsObject = new PhysicsObject(new SphereCollider(vec3(5.0f, 11.0f, 5.f), 1.0f), 10.0f, 0.0f,true);
	ballObject->getTransform()->translation = vec3(5.0f, 11.f, 5.0f); 
	//ballPhysicsObject->addForce(vec3(-1.0f, -9.8f, 0.0f)); 
	//SteeringBehavior* steeringBehavior = new SteeringBehavior(*this);
	ballPhysicsObject->m_UseGravity = true; 
	//steeringBehavior->addToList(vec3(0, 5, 0));
	//steeringBehavior->addToList(vec3(5, 0, 0));
	//steeringBehavior->addToList(vec3(0, 0, 5));
	//steeringBehavior->addToList(vec3(5, 0, 5));
	BallBehavior* ballBehavior = new BallBehavior(); 

	ballObject->addComponent(ballBehavior); 
	ballObject->addComponent(ballPhysicsObject); 
	//ballObject->addComponent(steeringBehavior); 
	ballObject->addComponent(ballMeshRenderer); 
	worldObject->addChild(ballObject); 
	
	//ball 2 
	//GameObject* ballObject2 = new GameObject(); 
	//MeshRenderer* ballMeshRenderer2= new MeshRenderer(new Mesh("Models/8Ball.fbx")); 
	//PhysicsObject* ballPhysicsObject2 = new PhysicsObject(new SphereCollider(vec3(0.f, 0.f, 0.f), 1.0f), 4.0f, 0.0f);
	//ballPhysicsObject2->addForce(vec3(0.0f, 2.f, 0.0f)); 
	//ballObject2->addComponent(ballPhysicsObject2); 
	//ballObject2->addComponent(ballMeshRenderer2); 
	//worldObject->addChild(ballObject2); 

	
	
	

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




TestGame::~TestGame()
{
}
