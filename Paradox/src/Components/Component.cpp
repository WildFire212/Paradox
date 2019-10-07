#include "Component.h"
#include"../core/GameObject.h"
#include"../Components/Transform.h"
namespace Paradox {
	namespace component {

Component::Component()
{
}

void Component::processEvents()
{
	
}

void Component::update(float deltaTime)
{
}

void Component::render(const RenderingEngine & renderingEngine) 
{
}


void Component::addToEngine(CoreEngine & engine)
{
	
}

void Component::setParent(GameObject* parent)
{
	m_Parent = parent; 
}

Component::~Component()
{
}
Transform * Component::getTransform()
{
	return m_Parent->getTransform();

}
} }
