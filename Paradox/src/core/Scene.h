#ifndef SCENE_H
#define SCENE_H
#include"../graphics/Window.h"
#include"GameObject.h"
#include<stdexcept>
#include"../graphics/ForwardRenderer.h"
#include<list>
using namespace Paradox::graphics; 
namespace Paradox {
	namespace core {

	
		class Scene {
		private: 
			std::list<ForwardRenderer*> m_ForwardRendererList; 
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
			auto addToForwardRendererList(ForwardRenderer* forwardRenderer) -> void; 
		private: 
			auto getRoot() -> GameObject*; 
			 
		};
}
} 
#endif