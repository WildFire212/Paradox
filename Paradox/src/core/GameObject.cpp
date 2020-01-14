#include "GameObject.h"
#include"../Components/PhysicsObject.h"
#include"PhysicsEngine.h"
namespace Paradox {
	namespace core {
		GameObject::GameObject()
		{
			m_Name = ""; 
			m_Transform = new Transform(); 
			m_Engine = nullptr; 
			m_Scene = nullptr; 
		}

		GameObject::GameObject(std::string name)
		{
			
			m_Name = name;
			m_Transform = new Transform();
			m_Engine = nullptr;
			m_Scene = nullptr;
			
		}

	
	

		void GameObject::processEvents()
		{

			m_Transform->update(); 
			
			for (Component* component : m_Components)
			{
				component->processEvents(); 
			}
		}

		void GameObject::update(float deltaTime)
		{
	
			for (Component* component : m_Components)
			{
				component->update(deltaTime);
			}
		}

		void GameObject::render(const RenderingEngine& engine) 
		{
			for (Component* component : m_Components)
			{
				component->render(engine);
			}
		}

		void GameObject::processEventsAll()
		{
			processEvents(); 
			for (GameObject* child : m_Children) {
				child->processEventsAll();
			}
		}

		void GameObject::updateAll(float deltaTime)
		{
			update(deltaTime);
			for (GameObject* child : m_Children) {
				child->updateAll(deltaTime);
			}
		}

		void GameObject::renderAll(const RenderingEngine & engine) 
		{
			render(engine); 

			for (GameObject* child : m_Children) {
				child->renderAll(engine); 
			}
		}

		void GameObject::addChild( GameObject* child)
		{
			m_Children.push_back(child);
			child->setEngine(*m_Engine);
			child->getTransform()->setParent(m_Transform); 
			//gameObject->setTransform().setParent(m_transform);
			for (Component* component : child->m_Components)
			{
				if (dynamic_cast<PhysicsObject*>(component))
				{
					PhysicsObject* physicsObject = static_cast<PhysicsObject*>(component);
					m_Engine->getPhysicsEngine().addPhysicsObject(physicsObject);
				}
			}
		}

		void GameObject::addComponent(Component * component)
		{
			m_Components.push_back(component);	
			component->setParent(this); 

			//return 
		}

		void GameObject::setEngine(CoreEngine& engine)
		{
			if (this->m_Engine != &engine)
			{
				this->m_Engine = &engine;
		   

				for (Component* component : m_Components) {
					component->addToEngine(engine); 
				}
				for (GameObject* child : m_Children) {
					child->setEngine(engine);
				}

			}
		}

		void GameObject::setScene(Scene * scene)
		{
			if (this->m_Scene != scene)
			{
				m_Scene = scene;
				for (GameObject* child : m_Children)
				{
					setScene(scene);
				}
			}
		}

		void GameObject::setName(std::string name)
		{
			m_Name = name; 
		}

		const std::string & GameObject::getName() const
		{
			// TODO: insert return statement here
			return m_Name; 
		}

		GameObject * GameObject::getObject(std::string name)
		{
			if (this->m_Name == name)
			{
				return this; 
			}
			else {

				for (GameObject* child : m_Children)
				{
					GameObject* search = child->getObject(name);
					if (search != nullptr)
					{
						return search;
					}
				}
			}

			
				return nullptr; 
			
		}

		Transform* GameObject::getTransform() const
		{
			return this->m_Transform;
		}


		void GameObject::move(vec3 Move)
		{
			m_Move = Move;
			if (!getComponent<PhysicsObject>())
			{
				m_Transform->move(Move); 
				m_Move = vec3(0, 0, 0); 
			}

		}

		GameObject::~GameObject()
		{
		}
	}
}