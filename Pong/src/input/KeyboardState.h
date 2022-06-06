#pragma once

#include "Key.h"

#include "GLFW/glfw3.h"

#include <unordered_map>

namespace input {
	class KeyboardState
	{
	private:
		std::unordered_map<unsigned int, Key> Keys;
	public:
		KeyboardState(GLFWwindow* window);
		bool KeyDown(unsigned int key);
	};
}

