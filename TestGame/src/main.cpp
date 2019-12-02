#define STB_IMAGE_IMPLEMENTATION

#include"core/CoreEngine.h"
#include<iostream>
#include"TestGame.h"

#if 0
using namespace Paradox::graphics; 
using namespace Paradox::maths; 
int main() {
	Paradox::graphics::Window window("Paradox",800, 600);
	window.Init(); 
	Camera* camera = new Camera(vec3(0,0.2f,0.3f), vec3(0,1.0f,0),0,0,0.5f,0.5f); 
	mat4 projection = mat4::Perpective(45.0f, 1, 0.1f, 100.0f);
	Texture texture("image_edited.jpg");
	Transform transform; 
	//transform.setTranslation(0.0,-0.5f, 0);
	//transform.setScale(2.0f, 2.0f, 2.0f);
	DirectionalLight* directionalLight = new DirectionalLight(1.0f, 1, 1.0f, 0.9f, 0.9f, glm::vec3(0, 0.0, -1.0f));
	Material material(0.8f, 0.8f); 
	EnvironmentSystem engine; 
	engine.setDirectionalLight(directionalLight); 
	engine.setCamera(camera);
	engine.setProjection(projection);
	GLfloat vertices[12] = {
		0.0f,0.3f,0.0f,
		0.3f,0.3f, 0.0f,
		0.3f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	};



	//mesh->TexCoords = new GLfloat[8]{
	//	0.0f, 0.0f,
	//	0.0f, 1.0f,
	//	1.0f, 1.0f,
	//	1.0f, 0.0f
	//	};
	 GLushort indices[6] = {
		0,1,2,
		2,3,0
	};

	 Mesh mesh(vertices, indices, 12, 6);
	Paradox::graphics::BasicShader shader("src/Shaders/GLSLShaders/MainShader.vert" , "src/Shaders/GLSLShaders/MainShader.frag"); 
	Paradox::graphics::MeshRenderer renderer; 

	while (!window.getWindowShouldClose())
	{
		//renderer.submit(&renderable);
		camera->mouseControl(window.getChangeX(), window.getChangeY()); 
		camera->keysControl(Window::m_Keys); 
	
		glClearColor(1, 1, 1, 1);
		window.clear(); 
		shader.bind();
		renderer.begin(); 
		shader.updateUniforms(transform, engine,material); 
		renderer.submit(mesh); 
		renderer.end(); 
		renderer.flush(); 
		window.update();
	}
	//system("PAUSE");
	return 0; 
}
#endif

using namespace Paradox::core; 
//using namespace Paradox::component; 

int main() {
	   
    	//	
//	audio.playSound();	

	TestGame game;	
	Paradox::core::CoreEngine core(game, "game ", 800, 800,120.f);	
	
		//temp code	audio
#if 0
	audio::Audio audio("Sound/stereo.wav");	
	 audio::Audio audio2("Sound/wave2.wav");
	 audio::Audio audio3("Sound/wave3.wav");
	 audio.setListener(maths::vec3(0,0.0f,0)); 
	
	 // ALuint buffer = audio.loadSound("Sound/stereo.wav"); 
	 audio::AudioSource audioSource; 
	 audio::AudioSource audioSource2; 
	 alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED); 
	 audioSource.setPitch(1.0f); 
	 audioSource.setVolume(1.0f); 
	 audioSource.setPosition(maths::vec3(-3.0f, 0.0f, 0.0f));
	 audioSource.setLooping(true); 
	// audioSource.playSound(audio2);	
	
				
	 audioSource2.setPitch(1.0f);
	 audioSource2.setVolume(0.1f);
	 audioSource2.setLooping(true); 
		
	 //audioSource.playSound(audio2); 
	 
	 audioSource2.playSound(audio3); 
	 
	 
	 for (float i = -3.0f; i < 3.0f;  i+=1.0f)
	 {
	     audioSource2.setPosition(maths::vec3(i, 0.0f, 0.0f));

		 std::chrono::duration<int, std::milli> timespan(1000);
		 std::this_thread::sleep_for(timespan);
	 }
#endif

	 core.start(); 
	// component::PhysicsObject phy(vec3(0, 0, 0), vec3(0.1f,0,0));
	 //phy.integrate(20.0f); 
	 std::getchar(); 

	 return 0; 

}