#include"Input.h"

namespace Paradox {
	namespace core {

		
			void Input::update() {

				upKeys.clear();
				for (int i = 0; i < MAX_KEYS; i++)
				{
					if (!getKey(i) && currKeysContain(i))
					{
						upKeys.push_back(i);
					}
				}
				downKeys.clear();
				for (int i = 0; i < MAX_KEYS; i++)
				{
					if (getKey(i) && !currKeysContain(i))
					{
						downKeys.push_back(i);
					}
				}
				currKeys.clear();
				for (int i = 0; i < MAX_KEYS; i++)
				{
					if (getKey(i))
					{
						currKeys.push_back(i);
					}
				}
			}


			bool Input::getKeyDown(int keycode) {
				return downKeysContain(keycode);
			}
			bool Input::getKey(int keycode) {
				return 	graphics::Window::getKeys(keycode);

			}

			bool Input::getKeyUp(int keycode) {
				return upKeysContain(keycode);
			}

			bool Input::downKeysContain(int i)
			{
				if (std::find(downKeys.begin(), downKeys.end(), i) != downKeys.end())
				{
					return true;
				}
				else {
					return false;
				}
			}
			bool Input::currKeysContain(int i)
			{
				if (std::find(currKeys.begin(), currKeys.end(), i) != currKeys.end())
				{
					return true;
				}
				else {
					return false;
				}
			}
			bool Input::upKeysContain(int i)
			{
				if (std::find(upKeys.begin(), upKeys.end(), i) != upKeys.end())
				{
					return true;
				}
				else {
					return false;
				}
			}

	}
}