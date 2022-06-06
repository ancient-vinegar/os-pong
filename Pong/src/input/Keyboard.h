#pragma once

#include "KeyboardState.h"

#include "GLFW/glfw3.h"

namespace input {
	class Keyboard
	{
	private:
		KeyboardState os;
		KeyboardState ns;
	public:
		Keyboard(GLFWwindow* window);
		void Update(GLFWwindow* window);

		bool KeyPressed(unsigned int key);
		bool KeyReleased(unsigned int key);
		bool KeyHeld(unsigned int key);
	};
}

