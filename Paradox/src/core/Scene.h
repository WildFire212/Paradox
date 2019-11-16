#pragma once
#include"../graphics/Window.h"
#include"GameObject.h"
#include<stdexcept>
using namespace Paradox::graphics; 
namespace Paradox {
	namespace core {

	
		class Scene {
		protected: 
			GameObject* m_Root; 
		public :
			virtual void init(); 
			virtual void processEvents(); 
			virtual void update(float deltaTime);
			virtual void render(RenderingEngine& renderingEngine); 
			void setEngine(CoreEngine& engine); 
			void addObject(GameObject* gameObject) ; 
			auto findObject(std::string name) -> GameObject* ; 
		private: 
			auto getRoot() -> GameObject*; 
			 
		};
}
} 