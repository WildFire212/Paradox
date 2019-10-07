#include "Scene.h"

namespace Paradox {
	namespace core {
void Scene::init()
{
	
}
	
void Scene::processEvents()
{
	getRoot()->processEventsAll(); 
}

void Scene::update(float deltaTime)
{ 
	getRoot()->updateAll( deltaTime); 
	
}
void Scene::render(RenderingEngine & renderingEngine)
{
	renderingEngine.render(getRoot()); 
}


void Scene::setEngine(CoreEngine & engine)
{
	getRoot()->setEngine(engine); 
}

void Scene::addObject(GameObject * gameObject)
{
	getRoot()->addChild(gameObject);

	getRoot()->setScene(this); 
}

GameObject * Scene::findObject(std::string name) 
{
	try {

		GameObject* search = getRoot()->getObject(name);
		if (search != nullptr)
		{
			return search;
		}
		else {
			
			throw std::runtime_error("RUNTIME ERROR : NO SUCH GAMEOBJECT WITH NAME '"+name+"' FOUND!");
		}

	}
	catch (std::runtime_error r)
	{
		std::cout << r.what()<< std::endl; 
		abort(); 
	}
	
}


GameObject * Scene::getRoot() 
{
	if (m_Root == NULL)
	{
		m_Root = new GameObject(); 
	}
	return m_Root; 
}
}}
