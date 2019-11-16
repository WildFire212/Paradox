#pragma once
#include"../graphics/Window.h"
#include<vector>

namespace Paradox {
	namespace core{
	class Input {
	private: 
		std::vector<int> downKeys; 
		std::vector<int> upKeys; 
		std::vector<int> currKeys;
	public:
		void update(); 
		auto getKeyDown(int keycode) -> bool;
		static auto getKey(int keycode) -> bool; 
		auto getKeyUp(int keycode) -> bool;
	private: 
		 auto downKeysContain(int i) -> bool; 
		auto currKeysContain(int i) -> bool; 
		auto upKeysContain(int i) -> bool; 
		

	};
	}
}