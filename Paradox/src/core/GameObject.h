#pragma once
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include<vector>
#include<algorithm>
#include"../Components/Component.h"
#include"../Components/Transform.h"
#include"RenderingEngine.h"
#include"../Shaders/Shader.h"
#include<string>
#include<stdexcept>
#endif

using namespace Paradox::component; 
using namespace Paradox::graphics; 
namespace Paradox {
	namespace core {

class GameObject
{
	
private: 
	std::string m_Name; 
	Scene* m_Scene; 
	std::vector<GameObject*> m_Children; 
	 std::vector<Component*> m_Components; 
	Transform* m_Transform; 
	CoreEngine* m_Engine; 
	Shader* m_Shader; 

	//movement 
public:
	vec3 m_Move; 
	GameObject();
	
	explicit GameObject(std::string name); 

	//game engine functions 
	virtual void processEvents() ;
	virtual void update(float deltaTime);
	virtual void render(const RenderingEngine& engine) ;

	virtual void processEventsAll(); 
	virtual void updateAll(float deltaTime) ;
	virtual void renderAll(const RenderingEngine& engine) ; 

	//addition of child and comoponent
	void addChild( GameObject* child);
	void addComponent(Component* component);

	//getters and setters 
	void setEngine(CoreEngine& engine); 
	void setScene(Scene* scene); 
	void setName(std::string name); 
	auto getName() const -> const std::string&; 
	auto getObject(std::string name) -> GameObject*; 
	auto getTransform() const -> Transform*; 
	template<class T> 
	inline auto getComponent() -> T* {
		try {
			for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
			{
				if (dynamic_cast<T*>(*it))
				{
					return dynamic_cast<T*>(*it);
				}

			}
			throw std::runtime_error("NO SUCH COMPONENT FOUND"); 
		}
		catch (std::runtime_error e)
		{
			std::cout << "GET COMPONENT ERROR : "<<e.what() << std::endl; 
		}
	}


	//additional 
	void move(vec3 Move); 
	~GameObject();
};

}

}
