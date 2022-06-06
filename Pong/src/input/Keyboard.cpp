#include "Keyboard.h"

input::Keyboard::Keyboard(GLFWwindow* window)
	: os(KeyboardState(window)), ns(KeyboardState(window))
{

}

void input::Keyboard::Update(GLFWwindow* window)
{
	os = ns;
	ns = KeyboardState(window);
}

bool input::Keyboard::KeyPressed(unsigned int key)
{
	return !os.KeyDown(key) && ns.KeyDown(key);
}

bool input::Keyboard::KeyReleased(unsigned int key)
{
	return os.KeyDown(key) && !ns.KeyDown(key);
}

bool input::Keyboard::KeyHeld(unsigned int key)
{
	return os.KeyDown(key) && ns.KeyDown(key);
}
