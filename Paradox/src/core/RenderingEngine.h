#pragma once
#include<vector>
#include"../Components/Camera.h"
#include"../graphics/GBuffer.h"
using namespace Paradox::component; 

using namespace Paradox::core; 
namespace Paradox {
	namespace core { class GameObject; }
	namespace component { class Light;  }
	namespace graphics {
 
class RenderingEngine
{
private: 
	std::vector<Light*> m_Lights; 
	Light* m_ActiveLight; 
	Camera* m_MainCamera; 
	GBuffer* m_GBuffer; 

public:
	RenderingEngine(int height, int width );
	~RenderingEngine();
	void render( GameObject* gameObject); 
	void addLight(Light* light); 
	auto getMainCamera() const -> const Camera&; 
	void setMainCamera(Camera* camera); 
	auto getActiveLight() const -> const Light*;
};
} }

