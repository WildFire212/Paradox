#pragma once
#include"Component.h"
#include"core/Input.h"
#include"core/GameObject.h"

using namespace Paradox::core; 
namespace Paradox {
	namespace component
	{
		 class Behavior : public Component {
		protected:

			void update(float deltaTime) override {
				
			}

		protected : 
			Behavior() = default;
			~Behavior() = default;

		};


} }