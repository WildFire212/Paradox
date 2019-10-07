#pragma once
#include"../core/CoreEngine.h"
#include"../maths/maths.h"

using namespace Paradox::core; 
using namespace Paradox::maths; 
using namespace Paradox::graphics; 
namespace Paradox {
namespace core { class GameObject; }
class Transform; 
	namespace component {

		
class Component
{
	
public : 
	GameObject* m_Parent; 
public:
	Component();
	

	virtual void processEvents();
	virtual void update(float deltaTime);
	virtual void render(const RenderingEngine& renderingEngine)  ;
	virtual void addToEngine(CoreEngine& engine);
	
	void setParent(GameObject* parent); 
	~Component();
	//getters
	Transform* getTransform() ;
};

} }
