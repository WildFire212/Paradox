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
		bool getKeyDown(int keycode);
		static bool getKey(int keycode); 
		bool getKeyUp(int keycode);
	private: 
		 bool downKeysContain(int i); 
		bool currKeysContain(int i); 
		bool upKeysContain(int i); 
		

	};
	}
}