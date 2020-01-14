#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H
#include"../graphics/ForwardRenderer.h"
#include"../graphics/CubeMap.h"
#include"../graphics/Mesh.h"

//singleton class skybox
namespace Paradox {
	namespace graphics {

	class Skybox : public ForwardRenderer {
	
private: 

	CubeMap* m_SkyboxCubeMap;
	Mesh* m_SkyMesh; 
	const char* SkyboxShaderVert = "src/Shaders/GLSLShaders/SkyboxShader.vert";
	const char* SkyboxShaderFrag = "src/Shaders/GLSLShaders/SkyboxShader.frag";
	
	//const string shader location
public : 

	static Skybox* getInstance(std::vector<std::string> faceLocations); 
	
	//yet to put on resource
	
	void render(const RenderingEngine& renderEngine) override; 

private: 
	
	//private constructor and destructor
	Skybox(std::vector<std::string> faceLocations);
	~Skybox() override {}
	//draw Skymesh
	auto renderSkyMesh()const  -> void ;
};
} }
#endif
